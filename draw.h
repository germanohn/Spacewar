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

#ifndef __DRAW_H__
#define __DRAW_H__

#include "body.h"
#include "vector.h"
#include "ship.h"
#include "projectile.h"
#include "simulation.h"

/* Inicializador do draw. Nessa função inicializamos todos os elementos da cena 
(objetos e background) e os objetos da allegro: display, event_queue, keyboard. */
int drawInit ();

/* Função que controla a dinâmica da cena durante a simulação */
void drawScene (double dt, Ship *player1, Ship *player2, Celula *head, Body *planet);

#endif
