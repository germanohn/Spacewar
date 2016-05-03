#include <stdio.h>
#include "simulation.h"

#define UNIVERSE_H 8e7
#define UNIVERSE_W 8e7

void updatePositions (double dt, Ship *player1, Ship *player2, Celula *head, Body *planet) {
    player1->body->angle = vectorAngle (player1->body->velocity);
    player2->body->angle = vectorAngle (player2->body->velocity);

    bodySetForce (player1->body, createVector (0, 0));
    bodySetForce (player2->body, createVector (0, 0));
    bodySetForce (planet, createVector (0, 0));

    /* Computa as forcas */
    applyForces (player1->body, player2->body);
    applyForces (player1->body, planet);
    applyForces (player2->body, planet);

    /* Move as naves */
    movement (player1->body, dt);
    movement (player2->body, dt);

    /* Aplica o toroide */
    if (fabs (player1->body->position->x) > (UNIVERSE_W / 2)) player1->body->position->x *= -1;
    if (fabs (player1->body->position->y) > (UNIVERSE_H / 2)) player1->body->position->y *= -1;
    if (fabs (player2->body->position->x) > (UNIVERSE_W / 2)) player2->body->position->x *= -1;
    if (fabs (player2->body->position->y) > (UNIVERSE_H / 2)) player2->body->position->y *= -1;

    /* Diminui o tempo de duração  */
    Celula *current = head->next, *previous = head;
    while (current != NULL) {
        current->proj->duration -= dt;

        if (current->proj->duration <= 0) {
            Celula *aux = current;
            previous->next = current->next;
            destroyProjectile (aux->proj);
            destroyCelula (aux);

        } else {
            current->proj->body->angle = vectorAngle (current->proj->body->velocity);
            movement (current->proj->body, dt);

        }

        previous = current;
        current = current->next;
    }
}
