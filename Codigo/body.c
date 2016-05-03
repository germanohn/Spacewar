#include <stdlib.h>
#include <math.h>
#include "body.h"

// Cria um objeto Body
Body* createBody (double radius, double weight, double x, double y, double vx, double vy) {
    Body* body = malloc (sizeof (Body));

    if (body != NULL) {
        body->position = createVector (x, y);
        body->velocity = createVector (vx, vy);
        body->radius = radius;
        body->weight = weight;
        body->force = createVector (0, 0);
        body->angle = 0.0;
    }

    return body;
}

// Destroi um objeto Body
void destroyBody (Body *body) {
    if (body == NULL) return;

    destroyVector (body->position);
    destroyVector (body->force);
    destroyVector (body->velocity);
    free (body);
}

// Setter da posição. Se houver uma anterior, destroi.
void bodySetPosition (Body *body, Vector *newPosition) {
    if (body == NULL) return;

    if (body->position != NULL) {
        destroyVector (body->position);
    }

    body->position = newPosition;
}

// Setter da força. Se houver uma anterior, destroi.
void bodySetForce (Body *body, Vector *newForce) {
    if (body == NULL) return;

    if (body->force != NULL) {
        destroyVector (body->force);
    }

    body->force = newForce;
}

// Setter da velocidade. Se houver uma anterior, destroi.
void bodySetVelocity (Body *body, Vector *newVelocity) {
    if (body == NULL) return;

    if (body->velocity != NULL) {
        destroyVector (body->velocity);
    }

    body->velocity = newVelocity;
}

// Aplica a força no body1 e body2 (ação e reação)
void applyForces (Body *body1, Body *body2) {
    if (body1 == NULL || body2 == NULL) return;

    double m = body1->weight;
    double M = body2->weight;
    double dist;

    /* Cria o vetor force com direção de body1 para body2 */
    Vector *force = createVector (body2->position->x - body1->position->x, body2->position->y - body1->position->y);
    dist = sqrt (vectorDotProduct (force, force));

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

// Dado um dt, aplica a força gerando uma acelação (modifica a velocidade)
// Por fim, ele aplica a velocidade no corpo.
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
