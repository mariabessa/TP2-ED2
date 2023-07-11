#ifndef Item_h
#define Item_h
#define MEMORIAMAX 2

typedef struct{
    long int inscricao;
    double nota;
    char estado[3];
    char cidade[51];
    char curso[31];
}Aluno;

typedef struct{
    FILE* fita[MEMORIAMAX];
}Fitas;
