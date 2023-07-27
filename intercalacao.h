#ifndef intercalacao_h
#define intercalacao_h
#include "Item.h"

typedef struct{
    Aluno aluno;
    int indice;
}EstruturaIntercalacao;

void iniciaItercalacao(FILE *, int, bool);
void intercala(Fitas, int, int,FILE*);
void iniciaDadosEstrutura(EstruturaIntercalacao *, int);

#endif