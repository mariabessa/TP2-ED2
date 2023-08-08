#ifndef intercalaSub_h
#define intercalaSub_h
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Item.h"

typedef struct{
    Aluno aluno;
    bool marcado;
} TipoSub;

int retornaMenorSub(TipoSub *);


#endif