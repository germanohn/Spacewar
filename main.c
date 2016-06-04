/***************************************************************/
/**                                                           **/
/**   Germano Huning Neuenfeld                      9298340   **/
/**   Lucas Moreira Santos                          9345064   **/
/**   Victor Wichmann Raposo                        9298020   **/
/**   Spacewar Fase 2                                         **/
/**   Professor:  Marco Dimas Gubitoso                        **/
/**   MAC0211 - Laboratório de Programação 1                  **/
/**                                                           **/
/***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include "body.h"
#include "vector.h"
#include "ship.h"
#include "projectile.h"
#include "draw.h"

#define DEBUG 0

void initObjects (Body **planet, Ship **player1, Ship **player2) {
    *planet = createBody (9e06, 6.02e24, 0, 0, 0, 0);
    *player1 = createShip ("Nave1", 1.6e6, 7.4e04, 3.5786e07, 0, 0, 0);
    *player2 = createShip ("Nave2", 1.6e6, 7.4e04, -3.5786e07, 0, 0, 0);
}

int main (int argc, char **argv) {
    if (argc != 2)
        fprintf (stderr, "errô\n");

    double dt = strtod (argv[1], NULL);

    Body *planet;
    Ship *player1;
    Ship *player2;
    Celula *head  = createCelula (NULL, NULL);

    initObjects (&planet, &player1, &player2);
    if (planet == NULL || player1 == NULL || player2 == NULL || drawInit () == -1) return -1;
    drawScene (dt, player1, player2, head, planet);

    destroyBody (planet);
    destroyShip (player1);
    destroyShip (player2);
    destroyAllCelulas (head);

    return 0;
}
