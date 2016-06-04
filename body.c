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
