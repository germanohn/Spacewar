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
