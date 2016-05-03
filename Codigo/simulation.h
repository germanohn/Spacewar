#ifndef __SIMULATION__
#define __SIMULATION__

#include "body.h"
#include "vector.h"
#include "ship.h"
#include "projectile.h"

void updatePositions (double dt, Ship *player1, Ship *player2, Celula *head, Body *planet);

#endif
