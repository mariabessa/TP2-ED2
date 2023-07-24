#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "intercalacao.h"
#include "Item.h"

void iniciaItercalacao(FILE *arq, int tam, int situacao, bool ArgOpcional){

    if(arq == NULL)
        return;

    //iniciando as fitas de entrada, lendo os dados e salvando nas respectivas fitas de destino.

    Fitas fitas;
    Aluno aluno; 
    char nomeArquivo[10];
    int numReg = tam/20; //calculando quantos blocos de registros serão inseridos nas fitas, ou seja, é a quantidade de registros a serem inseridos divididos por 20 que é o tamanho do bloco.

    fseek(arq, 0, SEEK_SET); //voltando pro início do arquivo.

    for(int i = 0; i < 20; i++){
        sprintf(nomeArquivo, "fita%d.bin", i + 1);
        fitas.fita[i] = fopen(nomeArquivo, "wb+");
    }

    for(int i = 0; i < numReg; i++){
        for(int j = 0; j < 20; j++){
            fread(&aluno, sizeof(Aluno), 1, arq);
            printf("%s\n", aluno.curso);
            fwrite(&aluno, sizeof(Aluno), 1, fitas.fita[i % 20]);
        }
    }
    
    //fechando os arquivos das fitas usadas
    for(int i = 0; i < 20; i++)
        fclose(fitas.fita[i]);
}

void intercala(Fitas entrada, int itens){

}