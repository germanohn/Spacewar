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

#ifndef __SHIP_H__
#define __SHIP_H__

#include "body.h"

typedef struct ship_struct {
    char *name;
    Body *body;
} Ship;

/* construtor e descontrutor do ship */
Ship* createShip (char *name, double x, double y, double vx, double vy, double weight);

void destroyShip (Ship *ship);

#endif
