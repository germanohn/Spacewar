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

// Destroi um objeto Celula
void destroyCelula (Celula *cel) {
    if (cel == NULL) return;
    
    //destroyProjectile (cel->proj);
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
