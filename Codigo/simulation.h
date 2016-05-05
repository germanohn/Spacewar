#ifndef __SIMULATION__
#define __SIMULATION__

#include "body.h"
#include "vector.h"
#include "ship.h"
#include "projectile.h"

/* Computa e aplica as forças nos corpos 1 e 2 */
void applyForces (Body *body1, Body *body2);

/* Move o corpo com a força aplicada */
void movement (Body *body, double dt);

void updatePositions (double dt, Ship *player1, Ship *player2, Celula *head, Body *planet);

#endif
