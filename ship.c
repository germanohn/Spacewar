#include <stdlib.h>
#include <math.h>
#include "ship.h"

// Cria um objeto Ship
Ship* createShip (char *name, double radius, double weight, double x, double y, double vx, double v) {
    Ship* ship = malloc (sizeof (Ship));

    if (ship != NULL) {
        ship->name = name;
        ship->body = createBody (radius, weight, x, y, vx, vy);
    }
    
    return ship;
}

// Retorna um array de Vectors com as posições dos vértices do triangulo
Vector** getShipVertex (Ship *ship) {
    Vector **v = malloc (3 * sizeof (Vector *));
    double angle = ship->body->angle;
    double sen0 = sin (angle);
    double cos0 = cos (angle);
    double sqrt3 = sqrt(3);

    // Determina os pontos iniciais para serem rotacionados.
    // Os pontos formam um triângulo equilatero.
    // Note que o eixo utilizado para rotação é o eixo Z centrado em (0,0).
    double  x1 = ship->body->radius * sqrt3 / 3,
            y1 = 0;
            
    double  x2 = - ship->body->radius * sqrt3 / 6,
            y2 = ship->body->radius / 2;
    
    double  x3 = - ship->body->radius * sqrt3 / 6,
            y3 = - ship->body->radius / 2;
    
    // Aplica a matriz de rotação fazendo uma mudança de eixo Z centrado nas posições iniciais
    v[0] = createVector (cos0 * x1 + sen0 * y1 + ship->body->position->x, -1 * sen0 * x1 + cos0 * y1 + ship->body->position->y);
    v[1] = createVector (cos0 * x2 + sen0 * y2 + ship->body->position->x, -1 * sen0 * x2 + cos0 * y2 + ship->body->position->y);
    v[2] = createVector (cos0 * x3 + sen0 * y3 + ship->body->position->x, -1 * sen0 * x3 + cos0 * y3 + ship->body->position->y);
    
    return v;
}

// Destroi um objeto Ship
void destroyShip (Ship *ship) {
    if (ship == NULL) return;
    
    free (ship->name);
    destroyBody (ship->body);
    free (ship);
}
