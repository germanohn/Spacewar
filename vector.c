#include <stdlib.h>
#include <math.h>
#include "vector.h"

// Cria um objeto Vector
Vector* createVector (double x, double y) {
    Vector* a = malloc (sizeof (Vector));

    if (a != NULL) {
        a->x = x;
        a->y = y;
    }

    return a;
}

// Destroi um objeto Vector
void destroyVector (Vector *vector) {
    if (vector == NULL) return;

    free (vector);
}

// Calcula a soma de dois vetores ('a' e 'b') colocando o resultado em 'a'
void vectorSum (Vector *a, Vector *b) {
    if (a == NULL || b == NULL) return;

    a->x += b->x;
    a->y += b->y;
}

// Calcula o produto interno entre dois vetores ('a' e 'b') e retorna um double
double vectorDotProduct (Vector *a, Vector *b) {
    if (a == NULL || b == NULL) return -1;

    double res;
    res = a->x*b->x + a->y*b->y;
    return res;
}

// Multiplica o vetor 'a' por um escalar 'x' direto no vetor 'a'
void vectorScalarProduct (Vector *a, double x) {
    if (a == NULL) return;

    a->x *= x;
    a->y *= x;
}

/* Calcula o angulo do vector a em relação ao eixo X (1, 0) */
double vectorAngle (Vector *a) {
  if (a->x == 0 && a->y == 0) return 0;
  return atan2 (a->y, a->x);
}
