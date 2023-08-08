#ifndef intercalaSub_h
#define intercalaSub_h
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Item.h"
#include "intercalacao.h"

typedef struct{
    Aluno aluno;
    bool marcado;
} TipoSub;

int retornaMenorSub(TipoSub *);
void iniciaIntercalacaoSub(FILE*, int, bool);
void intercalaSub(Fitas , int , FILE *);
void intercalaSaidaSub(Fitas, Fitas,int, int );
void intercalaEntradaSub(Fitas , Fitas ,int , int );





#endif