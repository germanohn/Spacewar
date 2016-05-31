#include <stdio.h>
#include <math.h>
#include "simulation.h"

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

void updateKeys (int *key, Body *body) {
    // atualiza o angulo
    if (key[KEY_LEFT]) {
        // aumenta o angulo
        body->angle -= 0.05;
    } else if (key[KEY_RIGHT]) {
        body->angle += 0.05;
    } 
    // acelera
    else if (key[KEY_UP]) {
        
    }

}

/* Atualiza a posição dos corpos */
void updatePositions (double dt, Ship *player1, Ship *player2, Celula *head, Body *planet) {
    bodySetForce (player1->body, createVector (0, 0));
    bodySetForce (player2->body, createVector (0, 0));
    bodySetForce (planet, createVector (0, 0));

    /* Computa as forcas */
    applyForces (player1->body, player2->body);
    applyForces (player1->body, planet);
    applyForces (player2->body, planet);

    /* Zera as forças sobre os projéteis */
    Celula *current = head->next, *previous = head;
    while (current != NULL) {
      bodySetForce (current->proj->body, createVector (0, 0));
      current = current->next;
    }

    /* Computa os movimentos dos projéteis */
    current = head->next, previous = head;
    while (current != NULL) {
        current->proj->duration -= dt;

        if (current->proj->duration <= 0) {
            Celula *aux = current;
            previous->next = current->next;
            destroyProjectile (aux->proj);
            destroyCelula (aux);

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
}
