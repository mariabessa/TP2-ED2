#ifndef quicksortExt_h
#define quicksortExt_h
#include "Item.h"
#include <limits.h>

typedef struct{
    Aluno vetor[MEMORIAMAX];
    int n;
}Pivo;

void quickSortInicia(int, int);
void QuicksortExterno(FILE **, FILE **, FILE **, int, int);
void particao(FILE **, FILE **, FILE **, Pivo, int, int, int *, int *);
void inicializaPivo(Pivo *);
void leSup(FILE **, Aluno *, int *, short *);
void leInf(FILE **, Aluno *, int *, short *);
void retiraMax(Pivo *, Aluno *);
void retiraMin(Pivo *, Aluno *);
void escreveMax(FILE **, Aluno, int *);
void escreveMin(FILE **, Aluno, int *);
void inserirPivo(Pivo *, Aluno);
void printa();

#endif