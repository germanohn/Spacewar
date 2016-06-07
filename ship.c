#include <stdlib.h>
#include <math.h>
#include "ship.h"

// Cria um objeto Ship
Ship* createShip (char *name, double radius, double weight, double x, double y, double vx, double vy) {
    Ship* ship = malloc (sizeof (Ship));

    if (ship != NULL) {
        ship->name = name;
        ship->body = createBody (radius, weight, x, y, vx, vy);
        ship->lastTimeShoot = 0;
    }

    return ship;
}

// Destroi um objeto Ship
void destroyShip (Ship *ship) {
    if (ship == NULL) return;

    // free (ship->name);
    destroyBody (ship->body);
    free (ship);
}
