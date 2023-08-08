#ifndef Item_h
#define Item_h
#include <stdio.h>
#define MEMORIAMAX 20

typedef struct{
    long int inscricao;
    double nota;
    char estado[3];
    char cidade[51];
    char curso[31];
}Aluno;

typedef struct{
    FILE* fita[MEMORIAMAX]; //vetor de ponteiro de arquivos
}Fitas;

typedef struct{
    int transf_leitura;
    int transf_escrita;
    int compara;
    double tempo;
}Analise;



#endif