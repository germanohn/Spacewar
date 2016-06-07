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
#include "allegro.h"
#include "menu_controller.h"

#define DEBUG 0

int main (int argc, char **argv) {
    if (argc != 2)
        fprintf (stderr, "errô\n");

    double dt = strtod (argv[1], NULL);

    if (allegroInit () == -1 || menuControllerInit ())
      return -1;

    menuControllerDraw (dt);
    allegroDestroy ();

    return 0;
}
