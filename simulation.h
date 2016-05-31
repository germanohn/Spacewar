#ifndef __SIMULATION__
#define __SIMULATION__

#include "body.h"
#include "vector.h"
#include "ship.h"
#include "projectile.h"

#define UNIVERSE_RATIO 1.5
#define UNIVERSE_H 8e7
#define UNIVERSE_W (UNIVERSE_H * UNIVERSE_RATIO)

/* Computa e aplica as forças nos corpos 1 e 2 */
void applyForces (Body *body1, Body *body2);

/* Move o corpo com a força aplicada */
void movement (Body *body, double dt);

/* Atualiza a posição dos corpos */
void updatePositions (double dt, Ship *player1, Ship *player2, Celula *head, Body *planet);

/* Teclas de controle das naves */
enum KEYS {
    KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};

/* Atualiza o movimento de um corpo de acordo com as teclas pressionada */
void updateKeys (int *key, Body *body);

#endif
