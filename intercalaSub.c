#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "intercalacao.h"
#include "ordenaInterno.h"
#include "Item.h"

void iniciaItercalacao(FILE *arq, int numReg, bool ArgOpcional){

    if(arq == NULL)
        return;

    //iniciando as fitas de entrada, lendo os dados e salvando nas respectivas fitas de destino.

    int numRegistros = numReg;
    Fitas fitas;
    Aluno alunos[20]; 
    char nomeArquivo[10];
    int j = 0;
    FILE *arqFinal = fopen("resultadoIntercalacao.bin", "wb+");

    fseek(arq, 0, SEEK_SET); //voltando pro início do arquivo.

    if(numReg <= 20){ //caso o número de registros seja menor do que o tamanho da memória principal, a intercalação não precisa ser feita, só a ordenação do vetor de alunos já basta.
        int i;
        if(ArgOpcional){ //if usado para verficar se o usuário quer que os dados sejam printados ou não ([-P]).
                for(i = 0; i < numReg; i++){
                    if(fread(&alunos[i], sizeof(Aluno), 1, arq) != 1)
                        break; 
                    printf("%s\n", alunos[i].cidade);
                    printf("%s\n", alunos[i].estado);
                    printf("%s\n", alunos[i].curso);
                    printf("%ld\n", alunos[i].inscricao);
                    printf("%lf\n", alunos[i].nota); //print dos dados antes de serem ordenados.
                }

                ordenaAlunos(alunos, i);

                for (i = 0; i < numReg; i++){
                    printf("%s\n", alunos[i].cidade);
                    printf("%s\n", alunos[i].estado);
                    printf("%s\n", alunos[i].curso);
                    printf("%ld\n", alunos[i].inscricao);
                    printf("%lf\n", alunos[i].nota); //print dos dados após de serem ordenados.
                } 

                for(int y = 0; y < numReg; y++)
                    fwrite(&alunos[y], sizeof(Aluno), 1, arqFinal);
            }
        else {
            for (i = 0; i < numReg; i++)
                if(fread(&alunos[j], sizeof(Aluno), 1, arq)!= 1) 
                    break;
            ordenaAlunos(alunos, i);
            for(int y = 0; y < numReg; y++)
                fwrite(&alunos[y], sizeof(Aluno), 1, arqFinal);
        }
        //função pra passar arquivo .bin para .txt
        fclose(arqFinal);
        return;
    }


    for(int i = 0; i < 20; i++){ //abertura das fitas de entrada, elas vão receber os valores do arquivo base.
        sprintf(nomeArquivo, "fita%d.bin", i + 1);
        fitas.fita[i] = fopen(nomeArquivo, "wb+");
    }
    
    //mexer daqui pra baixo
    //acessar fita x= fitas.fita[x]

    //gerar blocos pela seleção substituição
    //intercalação 2f depo
    //sempre que escrever um novo item, salvar em itemescrito, usar para compara 
}