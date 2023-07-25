#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "intercalacao.h"
#include "Item.h"

void iniciaItercalacao(FILE *arq, int numReg, bool ArgOpcional){

    if(arq == NULL)
        return;

    //iniciando as fitas de entrada, lendo os dados e salvando nas respectivas fitas de destino.

    Fitas fitas;
    Aluno alunos[20]; 
    char nomeArquivo[10];
    int j = 0;

    fseek(arq, 0, SEEK_SET); //voltando pro início do arquivo.

    for(int i = 0; i < 20; i++){
        sprintf(nomeArquivo, "fita%d.bin", i + 1);
        fitas.fita[i] = fopen(nomeArquivo, "wb+");
    }

    //O if e else a seguir é usado para verificar se a quantidade de registros de entrada é um número divisível por 20(que resulta em um inteiro), caso não seja, é feita uma manipulação dos dados para que uma fita fique com menos de 20 itens, mas garantindo que todos os itens sejam lidos.
    
    if(numReg % 20 != 0){
        int indice = 20;
        int indiceFita = 0;

        if(ArgOpcional){
            while(numReg >= 0){

                if(numReg >= 20)
                    indice = 20;
                else 
                    indice = numReg;

                //leitura dos vinte registros a serem organizados.
                for(j = 0; j < indice; j++){
                    if(fread(&alunos[j], sizeof(Aluno), 1, arq) != 1)
                        break; 
                    printf("%s\n", alunos[j].cidade);
                    printf("%s\n", alunos[j].curso);
                    printf("%s\n", alunos[j].estado);
                    printf("%ld\n", alunos[j].inscricao);
                    printf("%lf\n", alunos[j].nota);
                }

                ordenaAlunos(alunos, j);

                //inserção dos itens ordenados na fita.
                for(int y = 0; y <= j; y++)
                    fwrite(&alunos[y], sizeof(Aluno), 1, fitas.fita[indiceFita % 20]);

                fseek(fitas.fita[indiceFita % 20], 0, SEEK_SET);

                numReg -= 20;
                indiceFita++;
            }
        }
        else {
            while(numReg >= 0){

                if(numReg >= 20)
                    indice = 20;
                else 
                    indice = numReg;

                //leitura dos vinte registros a serem organizados.
                for(j = 0; j < indice; j++)
                    if(fread(&alunos[j], sizeof(Aluno), 1, arq) != 1)
                        break;  
                
                ordenaAlunos(alunos, j);

                //inserção dos itens ordenados na fita.
                for(int y = 0; y <= j; y++)
                    fwrite(&alunos[y], sizeof(Aluno), 1, fitas.fita[indiceFita % 20]);
                
                fseek(fitas.fita[indiceFita % 20], 0, SEEK_SET);

                numReg -= 20;
                indiceFita++;
            }
        }
    }
    else{
        printf("entrou no segundo\n");
        int numBlocos = numReg/20;
        if(ArgOpcional){
            for(int i = 0; i < numBlocos; i++){
                //leitura dos vinte registros a serem organizados.
                for(j = 0; j < 20; j++){
                    fread(&alunos[j], sizeof(Aluno), 1, arq);
                    printf("%s\n", alunos[j].cidade);
                    printf("%s\n", alunos[j].curso);
                    printf("%s\n", alunos[j].estado);
                    printf("%ld\n", alunos[j].inscricao);
                    printf("%lf\n", alunos[j].nota);
                }

                ordenaAlunos(alunos, 20);

                //inserção dos itens ordenados na fita.
                for(int y = 0; y <= j; y++)
                    fwrite(&alunos[y], sizeof(Aluno), 1, fitas.fita[i % 20]);

                fseek(fitas.fita[i % 20], 0, SEEK_SET);
            }
        }
        else {
            for(int i = 0; i < numBlocos; i++){

                //leitura dos vinte registros a serem organizados.
                for(j = 0; j < 20; j++)
                    if(fread(&alunos[j], sizeof(Aluno), 1, arq) != 1)
                        break;  
                
                ordenaAlunos(alunos, j);

                //inserção dos itens ordenados na fita.
                for(int y = 0; y <= j; y++)
                    fwrite(&alunos[y], sizeof(Aluno), 1, fitas.fita[i % 20]);
                
                fseek(fitas.fita[i % 20], 0, SEEK_SET);
            }
        }
    }

    //fechando os arquivos das fitas usadas
    for(int i = 0; i < 20; i++)
        fclose(fitas.fita[i]);
}

void ordenaAlunos(Aluno *vetorAlunos, int tam){
    //ordena os blocos das fitas
}

void intercala(Fitas entrada, int itens){

}