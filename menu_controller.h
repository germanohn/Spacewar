#ifndef __MENU_H___
#define __MENU_H__
#include "allegro.h"
#include "game_controller.h"

int menuControllerInit ();
void menuControllerDraw (double dt, Ship *player1, Ship *player2, Celula *head, Body *planet);

#endif
