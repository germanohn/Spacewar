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

#ifndef __BODY_H__
#define __BODY_H__

#include "vector.h"
#define CONST_GRAVITACIONAL 6.67e-11

typedef struct body_struct {
    double radius;
    double weight;
    double angle;
    Vector *position;
    Vector *force;
    Vector *velocity;
} Body;

/* Construtor e descontrutor do body */
Body* createBody (double radius, double weight, double x, double y, double vx, double vy);
void destroyBody (Body *body);

#endif
