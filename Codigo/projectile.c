#include <stdlib.h>
#include <math.h>
#include "projectile.h"

// Cria um objeto Celula
Celula* createCelula (Projectile *proj, Celula *next) {
    Celula *cel = malloc (sizeof (Celula));
    
    if (cel != NULL) {
        cel->proj = proj;
        cel->next = next;
    }
    
    return cel;
}

// Retorna um array de Vectors com as posições dos vértices do projetil
Vector** getProjectileVertex (Projectile *proj) {
    Vector **v = malloc (4 * sizeof (Vector *));
    Vector *xAxis = createVector (1, 0);
    double cos0, sen0, angle;
    
    double lengthVelocity = vectorDotProduct (proj->body->velocity, proj->body->velocity);

    if (lengthVelocity == 0) {
        cos0 = 1;
        angle = 0;
        sen0 = 0;

    } else {
        cos0 = vectorDotProduct(proj->body->velocity, xAxis) / sqrt(lengthVelocity);
        angle = acos (cos0);
        sen0 = sin (angle);

        // COMO UM DOS VETORES É (1, 0), O PROD VETORIAL SERÁ (proj->body->velocity->y)
        if (proj->body->velocity->y > 0)
            sen0 *= -1;
    }

    
    destroyVector (xAxis);
    
    double  x1 = 3 * proj->body->radius * 0.3,
            y1 = proj->body->radius * 0.1;
            
    double  x2 = 3 * proj->body->radius * 0.3,
            y2 = - proj->body->radius * 0.1;
            
    double  x3 = - 3 * proj->body->radius * 0.3,
            y3 = - proj->body->radius * 0.1;
            
    double  x4 = - 3 * proj->body->radius * 0.3,
            y4 = proj->body->radius * 0.1;
    
    
    v[0] = createVector (cos0 * x1 + sen0 * y1 + proj->body->position->x, -1 * sen0 * x1 + cos0 * y1 + proj->body->position->y);
    v[1] = createVector (cos0 * x2 + sen0 * y2 + proj->body->position->x, -1 * sen0 * x2 + cos0 * y2 + proj->body->position->y);
    v[2] = createVector (cos0 * x3 + sen0 * y3 + proj->body->position->x, -1 * sen0 * x3 + cos0 * y3 + proj->body->position->y);
    v[3] = createVector (cos0 * x4 + sen0 * y4 + proj->body->position->x, -1 * sen0 * x4 + cos0 * y4 + proj->body->position->y);
    
    return v;
}

// Destroi um objeto Celula
void destroyCelula (Celula *cel) {
    if (cel == NULL) return;
    
    destroyProjectile (cel->proj);
    free (cel);
}

// Destroi a lista ligada dado uma cabeça "cel"
void destroyAllCelulas (Celula *cel) {
    if (cel == NULL) return;
    
    destroyAllCelulas (cel->next);
    destroyCelula (cel);
}

// Cria um objeto Projectile
Projectile* createProjectile (double duration, double weight, double x, double y, double vx, double vy) {
    Projectile* projectile = malloc (sizeof (Projectile));

    if (projectile != NULL) {
        projectile->duration = duration;
        projectile->body = createBody (8e5, weight, x, y, vx, vy);
    }
    
    return projectile;
}

// Destroi um objeto Projectile
void destroyProjectile (Projectile *projectile) {
    if (projectile == NULL) return;
    
    destroyBody (projectile->body);
    free (projectile);
}
