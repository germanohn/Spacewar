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

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#define DISPLAY_H 800
#define DISPLAY_W (DISPLAY_H * UNIVERSE_RATIO)
#define SCALE_X (DISPLAY_W / UNIVERSE_W)
#define SCALE_Y (DISPLAY_H / UNIVERSE_H)

/* Inicializador do allegro. Retorna 0 se inicializou, qualquer coisa do contrário. */
int allegroInit ();

#endif
