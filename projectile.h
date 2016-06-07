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

#ifndef __PROJECTILE_H__
#define __PROJECTILE_H__

#include "body.h"

/* Struct do vetor */
typedef struct projectile_struct {
    double duration;
    int playerIdentifier;
    Body *body;
} Projectile;

/* construtor e descontrutor do vetor */
Projectile* createProjectile (double duration, double weight, double x, double y, double vx, double vy, int playerID);
void destroyProjectile (Projectile *projectile);

typedef struct celula_struct {
    Projectile *proj;
    struct celula_struct *next;
} Celula;

/* Construtor e destructor de Celula*/
Celula *createCelula (Projectile *proj, Celula *prox);
void destroyCelula (Celula *cel);
void destroyAllCelulas (Celula *cel);

#endif
