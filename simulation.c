#include <stdio.h>
#include <math.h>
#include "simulation.h"
#define MAX_PROJECTILES 50

int NUM_PROJECTILES;

void applyForces (Body *body1, Body *body2) {
    if (body1 == NULL || body2 == NULL) return;

    double m = body1->weight;
    double M = body2->weight;
    double dist;

    /* Cria o vetor force com direção de body1 para body2 */
    Vector *force = createVector (body2->position->x - body1->position->x, body2->position->y - body1->position->y);
    dist = sqrt (vectorDotProduct (force, force));

    /* Se a distância for NaN ou menor que um epsilon = 1e-15, então não aplicamos força pois como não há colisão,
       dois corpos podem estar numa posição muito próxima (ou na mesma posição). */
    if (isnan(dist) || fabs (dist) < 1e-15) return;

    /* Deixa o vetor force unitário */
    vectorScalarProduct (force, 1.0 / dist);

    /* Multiplica o vetor force por (CONST_GRAVITACIONAL * m * M / dist^2) */
    vectorScalarProduct (force, CONST_GRAVITACIONAL * m * M / (dist*dist));
    vectorSum (body1->force, force); // Aplica a força no corpo 1

    /* Calcula o vetor reação */
    vectorScalarProduct (force, -1);
    vectorSum (body2->force, force); // Aplica a força contrária no corpo 2

    destroyVector(force);
}

void movement (Body *body, double dt) {
    if (body == NULL) return;

    Vector *a = createVector (body->force->x, body->force->y);
    vectorScalarProduct (a, 1.0 / body->weight);

    /* Calcula a posição */
    body->position->x = body->position->x + body->velocity->x * dt + (a->x * dt * dt) / 2;
    body->position->y = body->position->y + body->velocity->y * dt + (a->y * dt * dt) / 2;

    /* Calcula a velocidade */
    body->velocity->x = body->velocity->x + a->x * dt;
    body->velocity->y = body->velocity->y + a->y * dt;

    destroyVector (a);
}

// Recebe uma celula e destroi a proxima retornando a anterior
Celula *projectileDestroyed (Celula *cel) {
    if (cel == NULL) return NULL;

    // celula a ser destruida
    Celula *lixo = cel->next;

    // nova celula que cel ira apontar
    cel->next = lixo->next;
    destroyCelula (lixo);

    return cel->next;
}

int willColide (Body *a, Body *b) {
    double deltaX = a->position->x - b->position->x;
    double deltaY = a->position->y - b->position->y;
    //printf ("deltaX %lf deltaY %lf a->radius %lf b->radius", deltaX, deltaY, a->radius, b->radius);
    return sqrt(deltaX * deltaX + deltaY * deltaY) < (a->radius + b->radius);
}

int verifyColission (Ship *player1, Ship *player2, Body *planet, Celula *head) {
    if (willColide (player1->body, planet) ||         // Player 1 <> Planeta
            willColide (player2->body, planet) ||         // Player 2 <> Planeta
            willColide (player1->body, player2->body)) {  // Player 1 <> Player 2
        return 1;

    }

    Celula *current = head->next, *previous = head;
    while (current != NULL) {
        if (willColide (current->proj->body, player1->body) ||
                willColide (current->proj->body, player2->body)) {
            return 1;

        }

        if (willColide (current->proj->body, planet)) {
            current = projectileDestroyed (previous);
            NUM_PROJECTILES--;
            continue;

        }
        int currentDestroyed = 0;
        Celula *innerCurrent = current->next, *innerPrevious = current;
        while (innerCurrent != NULL) {
            if (willColide (current->proj->body, innerCurrent->proj->body)) {
                innerCurrent = projectileDestroyed (innerPrevious);
                current = projectileDestroyed (previous);
                NUM_PROJECTILES -= 2;
                currentDestroyed = 1;
                break;
            }

            innerPrevious = innerCurrent;
            innerCurrent  = innerCurrent->next;
        }

        if (currentDestroyed == 0) {
            previous = current;
            current = current->next;
        }
    }

    return 0;
}

void updateKeys (int *key, Body *body, Celula *head) {
    // atualiza o angulo
    if (key[KEY_LEFT]) {
        // diminui o angulo
        body->angle -= 0.08;
    } else if (key[KEY_RIGHT]) {
        body->angle += 0.08;
    } else if (key[KEY_UP]) {
        // acelera
        // o vetor velocidade ganha mais um componente na direção da nave
        // que será k * (cos0, sen0), tal que k é um constante e (cos0, sen0)
        // é o vetor unitário na direção da nave
        int k = 100, limit = 4.5e3;
        Vector *vel = createVector (k * cos (body->angle), k * sin (body->angle));
        vectorSum (body->velocity, vel);
        // modulo do vetor body->velocity para verificar se passou do limite de velocidade
        double mod = sqrt (vectorDotProduct (body->velocity, body->velocity));
        if (mod > limit)
            vectorScalarProduct (body->velocity, (double) limit / mod);

        destroyVector (vel);

    } else if (key[KEY_DOWN]) {
        if (NUM_PROJECTILES < MAX_PROJECTILES) {
          int k = 5e3;
          Vector *vel = createVector (k * cos (body->angle), k * sin (body->angle));

          Projectile *proj = createProjectile (3e4, 1e09,
                  body->position->x + cos (body->angle) * (body->radius + 1e6),
                  body->position->y + sin (body->angle) * (body->radius + 1e6),
                  vel->x, vel->y);
          head->next = createCelula (proj, head->next);
          NUM_PROJECTILES++;

          destroyVector (vel);
        }

        key[KEY_DOWN] = 0;
    }
}

/* Atualiza a posição dos corpos */
int updatePositions (double dt, Ship *player1, Ship *player2, Celula *head, Body *planet) {
    vectorSetValue (player1->body->force, 0, 0);
    vectorSetValue (player2->body->force, 0, 0);
    vectorSetValue (planet->force, 0, 0);

    /* Computa as forcas */
    applyForces (player1->body, player2->body);
    applyForces (player1->body, planet);
    applyForces (player2->body, planet);

    /* Zera as forças sobre os projéteis */
    Celula *current = head->next, *previous = head;
    while (current != NULL) {
        vectorSetValue (current->proj->body->force, 0, 0);
        current = current->next;
    }

    /* Computa os movimentos dos projéteis */
    current = head->next, previous = head;
    while (current != NULL) {
        current->proj->duration -= dt;

        if (current->proj->duration <= 0) {
            Celula *aux = current;
            previous->next = current->next;
            destroyCelula (aux);
            NUM_PROJECTILES--;

        } else {
            Celula *curForce = current->next;
            while (curForce != NULL) {
                applyForces (current->proj->body, curForce->proj->body);
                curForce = curForce->next;
            }

            applyForces (current->proj->body, player1->body);
            applyForces (current->proj->body, player2->body);
            applyForces (current->proj->body, planet);

            movement (current->proj->body, dt);
            current->proj->body->angle = vectorAngle (current->proj->body->velocity);
            if (fabs (current->proj->body->position->x) > (UNIVERSE_W / 2)) current->proj->body->position->x *= -1;
            if (fabs (current->proj->body->position->y) > (UNIVERSE_H / 2)) current->proj->body->position->y *= -1;

        }

        previous = current;
        current = current->next;
    }

    /* Move as naves */
    movement (player1->body, dt);
    movement (player2->body, dt);

    /* Aplica o toroide */
    if (fabs (player1->body->position->x) > (UNIVERSE_W / 2)) player1->body->position->x *= -1;
    if (fabs (player1->body->position->y) > (UNIVERSE_H / 2)) player1->body->position->y *= -1;
    if (fabs (player2->body->position->x) > (UNIVERSE_W / 2)) player2->body->position->x *= -1;
    if (fabs (player2->body->position->y) > (UNIVERSE_H / 2)) player2->body->position->y *= -1;

    /* Verifica colisão */
    return verifyColission (player1, player2, planet, head);
}
