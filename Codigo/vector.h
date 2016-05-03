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

#ifndef __VECTOR_H__
#define __VECTOR_H__


/* Struct do vetor */
typedef struct vector_struct {
    double x;
    double y;
} Vector;

/* construtor e descontrutor do vetor */
Vector* createVector (double x, double y);
void destroyVector (Vector *vector);

/* retorna a soma (a + b) */
void vectorSum (Vector *a, Vector *b);

/* retorna o produto interno de a e b */
double vectorDotProduct (Vector *a, Vector *b);

/* multiplica o vetor a por x */
void vectorScalarProduct (Vector *a, double x);


#endif