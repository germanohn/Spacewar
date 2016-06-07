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

#ifndef __GAME_H__
#define __GAME_H__

#include "body.h"
#include "vector.h"
#include "ship.h"
#include "projectile.h"
#include "simulation.h"

/* Inicializador do draw. Nessa função inicializamos todos os elementos da cena
(objetos e background) e os objetos da allegro: display, event_queue, keyboard. */
int gameControllerInit ();

/* Função que controla a dinâmica da cena durante a simulação */
void gameControllerDraw (double dt, Ship *player1, Ship *player2, Celula *head, Body *planet);

/* Função que destroi os elementos da cena depois que o jogo acabou */
void gameControllerDestroy ();

/* Callback de quando um projectile é adicionado */
void gameControllerProjectileAdded ();

#endif
