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

Ship* readShip () {
    double x, y, vx, vy, weight;
    char* name = malloc (sizeof(char) * 100);

    scanf ("%s %lf", name, &weight);
    scanf ("%lf %lf", &x, &y);
    scanf ("%lf %lf", &vx, &vy);

    return createShip (name, x, y, vx, vy, weight);
}

Projectile* readProjectile (double duration) {
    double x, y, vx, vy, weight;

    scanf ("%lf", &weight);
    scanf ("%lf %lf", &x, &y);
    scanf ("%lf %lf", &vx, &vy);

    return createProjectile (duration, weight, x, y, vx, vy);
}

Body* readPlanet () {
    double radius, weight;

    scanf ("%lf %lf", &radius, &weight);

    return createBody (radius, weight, 0, 0, 0, 0);
}

int main (int argc, char **argv) {
    if (argc != 2)
        fprintf (stderr, "errô\n");

    double simulation;
    int j;
    double duration_projectile;
    int num_projectiles;
    double dt = strtod (argv[1], NULL);

    Body *planet;
    Ship *player1;
    Ship *player2;
    Celula *head = createCelula (NULL, NULL);

    /* Planeta */
    planet = readPlanet ();

    /* Tempo de Simulação */
    scanf ("%lf", &simulation);

    /* Player 1 */
    player1 = readShip ();

    /* Player 2 */
    player2 = readShip ();

    if (planet == NULL || player1 == NULL || player2 == NULL) {
        printf("Erro ao instanciar planeta, player1 e/ou player2.\n");
        return 0;
    }

    scanf("%d %lf", &num_projectiles, &duration_projectile);

    for (j = 0; j < num_projectiles; j++) {
        Projectile *proj = readProjectile (duration_projectile);
        head->next = createCelula (proj, head->next);
    }
    if (drawInit () == -1) return -1;
    drawScene (dt, simulation, player1, player2, head, planet);

    destroyBody (planet);
    destroyShip (player1);
    destroyShip (player2);
    destroyAllCelulas (head);

    return 0;
}
