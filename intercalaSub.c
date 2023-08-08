#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "intercalacao.h"
#include "intercalaSub.h"
#include "ordenaInterno.h"
#include "Item.h"

void iniciaItercalacaoSub(FILE *arq, int numReg, bool ArgOpcional){

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
    
    TipoSub pivo[20];

    for(int x = 0; x < 20; x++){
        fread(&pivo[x].aluno, sizeof(Aluno), 1, arq);
        pivo[x].marcado = false;
    }

    int fitaASerEscrita = 0;
    int casasMarcadas = 0;
    int blocosCompletos = 0;
    int indiceMenor = retornaMenorSub(pivo);
    double notaMenor = pivo[indiceMenor].aluno.nota;

    for(int j = 0; j < numReg - 20; j++){
        if(casasMarcadas == 20){
            blocosCompletos++;
            if (blocosCompletos == 20)
                intercala();
            fitaASerEscrita++;
            for(int y = 0; y < 20; y++)
                pivo[y].marcado = false;
        }
        if(indiceMenor != -1){
            fwrite(&pivo[indiceMenor].aluno, sizeof(Aluno), 1, fitas.fita[fitaASerEscrita%20]);
            fread(&pivo[indiceMenor].aluno, sizeof(Aluno), 1, arq);
        }
        if(pivo[indiceMenor].aluno.nota < notaMenor){
            pivo[indiceMenor].marcado = true;
            casasMarcadas++;
        }
        indiceMenor = retornaMenorSub(pivo);
    }
}

int retornaMenorSub(TipoSub *vetor){
    double menor = 10001;
    int indiceMenor = -1;

    for(int i = 0; i < 20; i++){
        if(vetor[i].aluno.nota < menor && vetor[i].marcado == false){
            menor = vetor[i].aluno.nota;
            indiceMenor = i;
        }
    }
    
    return indiceMenor;
}