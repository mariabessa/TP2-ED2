#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #include "Item.h"
#define MEMORIAMAX 20


typedef struct{
    int inscricao;
    double nota;
    char estado[3];
    char cidade[51];
    char curso[31];
}Aluno;


int main() {
// void lerArquivo() {
    FILE *arquivo;
    Aluno alunos;
    int inscricao;
    double nota;
    char estado[3];
    char cidade[51];
    char curso[31];
    char espaco;
    int tam = 0;

    if((arquivo = fopen("arquivo.txt", "r")) == NULL) {
        puts("Arquivo nao pode ser aberto...");
        return 0;
    }

    while(fscanf(arquivo, "%d %lf", &inscricao, &nota) != EOF && tam++ <= MEMORIAMAX) {
        fscanf(arquivo, "%c", &espaco);
        fgets(estado, 3, arquivo);
    
        fscanf(arquivo, "%c", &espaco);
        fgets(cidade, 51, arquivo);

        fscanf(arquivo, "%c", &espaco);
        fgets(curso, 31, arquivo);
        alunos.inscricao = inscricao;
        alunos.nota = nota;
        strcpy(alunos.estado, estado);
        strcpy(alunos.cidade, cidade);
        strcpy(alunos.curso, curso);

        



        printf("%.08d %lf %s %s %s\n", alunos.inscricao, alunos.nota, alunos.estado, alunos.cidade, alunos.curso);
    }

    

    fclose(arquivo);

    return 0;
}