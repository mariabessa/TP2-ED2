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
        //funçãoparapassarbinparatxt 
        fclose(arqFinal);
        return;
    }


    for(int i = 0; i < 20; i++){ //abertura das fitas de entrada, elas vão receber os valores do arquivo base.
        sprintf(nomeArquivo, "fita%d.bin", i + 1);
        fitas.fita[i] = fopen(nomeArquivo, "wb+");
    }

    //O if e else a seguir é usado para verificar se a quantidade de registros de entrada é um número divisível por 20(que resulta em um inteiro), caso não seja, é feita uma manipulação dos dados para que uma fita fique com menos de 20 itens, mas garantindo que todos os itens sejam lidos.
    if(numReg % 20 != 0){
        int registrosPorFita = 20;
        int indiceFita = 0;

        if(ArgOpcional){ //if usado para verficar se o usuário quer que os dados sejam printados ou não ([-P]).
            while(numReg > 0){
                
                if(numReg >= 20)
                    registrosPorFita = 20;
                else 
                    registrosPorFita = numReg;

                //leitura dos vinte registros a serem organizados.
                for(j = 0; j < registrosPorFita; j++){
                    if(fread(&alunos[j], sizeof(Aluno), 1, arq) != 1)
                        break; 
                    printf("%s\n", alunos[j].cidade);
                    printf("%s\n", alunos[j].curso);
                    printf("%s\n", alunos[j].estado);
                    printf("%ld\n", alunos[j].inscricao);
                    printf("%lf\n", alunos[j].nota); //print dos dados antes de serem ordenados.
                }

                ordenaAlunos(alunos, j);

                for (int i = 0; i < numReg; i++){
                    printf("%s\n", alunos[i].cidade);
                    printf("%s\n", alunos[i].estado);
                    printf("%s\n", alunos[i].curso);
                    printf("%ld\n", alunos[i].inscricao);
                    printf("%lf\n", alunos[i].nota); //print dos dados após de serem ordenados.
                }

                //inserção dos itens ordenados na fita.
                for(int y = 0; y < j; y++)
                    fwrite(&alunos[y], sizeof(Aluno), 1, fitas.fita[indiceFita % 20]);
                numReg -= 20;
                indiceFita++;
            }
        }
        else {
            while(numReg > 0){

                if(numReg >= 20)
                    registrosPorFita = 20;
                else 
                    registrosPorFita = numReg;

                //leitura dos vinte registros a serem organizados.
                for(j = 0; j < registrosPorFita; j++)
                    if(fread(&alunos[j], sizeof(Aluno), 1, arq) != 1)
                        break;  
                
                ordenaAlunos(alunos, j);

                //inserção dos itens ordenados na fita.
                for(int y = 0; y < j; y++)
                    fwrite(&alunos[y], sizeof(Aluno), 1, fitas.fita[indiceFita % 20]);
                numReg -= 20;
                indiceFita++;
            }
        }
    }
    else{
        int numBlocos = numReg/20;
        if(ArgOpcional){ //if usado para verficar se o usuário quer que os dados sejam printados ou não ([-P]).
            for(int i = 0; i < numBlocos; i++){
                //leitura dos vinte registros a serem organizados.
                printf("entrou\n");
                for(j = 0; j < 20; j++){
                    if(fread(&alunos[j], sizeof(Aluno), 1, arq)!= 1) 
                        break;
                    printf("%s\n", alunos[j].cidade);
                    printf("%s\n", alunos[j].curso);
                    printf("%s\n", alunos[j].estado);
                    printf("%ld\n", alunos[j].inscricao);
                    printf("%lf\n", alunos[j].nota); //print dos dados antes de serem ordenados.
                }

                ordenaAlunos(alunos, 20);

                for (int i = 0; i < numReg; i++){
                    printf("%s\n", alunos[i].cidade);
                    printf("%s\n", alunos[i].estado);
                    printf("%s\n", alunos[i].curso);
                    printf("%ld\n", alunos[i].inscricao);
                    printf("%lf\n", alunos[i].nota); //print dos dados após de serem ordenados.
                }

                //inserção dos itens ordenados na fita.
                for(int y = 0; y < j; y++)
                    fwrite(&alunos[y], sizeof(Aluno), 1, fitas.fita[i % 20]);
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
                for(int y = 0; y < j; y++)
                    fwrite(&alunos[y], sizeof(Aluno), 1, fitas.fita[i % 20]);
            }
        }
    }

    for (int i = 0; i < 20; i++)
        fseek(fitas.fita[i], 0, SEEK_SET); //voltando pro início do arquivo de todas as fitas.

    //A seguir temos o print de todos os registros de todos os blocos de todas as fitas (caso a quantidade de registros seja divisivel por 20).

    // Aluno aluno; 
    // fseek(fitas.fita[0], 0, SEEK_SET);
    // for(int j = 0; j < 20; j++){ //for de fitas
    //     printf("Fita: %d\n\n", j+1);
    //     int count = 0;
    //     for(int i = 0; i < 20; i ++){ //for de blocos
    //         count++;
    //         for(int y = 0; y < 20; y++){ //for de registros
    //             if(fread(&aluno, sizeof(Aluno), 1, fitas.fita[j])!= 1) 
    //                 break;

    //             printf("Bloco: %d\n", count);
    //             printf("%s\n", aluno.cidade);
    //             printf("%s\n", aluno.curso);
    //             printf("%s\n", aluno.estado);
    //             printf("%ld\n", aluno.inscricao);
    //             printf("%lf\n\n", aluno.nota);
    //         }
    //     }
    //     printf("\n\n");
    // }
    // for (int i = 0; i < 20; i++)
    //     fseek(fitas.fita[i], 0, SEEK_SET); //voltando pro início do arquivo de todas as fitas.

          
    intercala(fitas, numRegistros, arqFinal);
    //funçãoparapassarbinparatxt
    fclose(arqFinal);
    
    
    //fechando os arquivos das fitas usadas
    for(int i = 0; i < 20; i++)
        fclose(fitas.fita[i]);
}

void intercala(Fitas fitasEntrada, int numRegistros, FILE *arqFinal){

    int numRepeticoesGerais = 1; 
    Fitas fitasSaida; 
    char nomeArquivo[10];

    if(numRegistros > 400){ //contabiliza quantas transições de fitas de entrada vão ocorrer.
        for(int i = 400; i < numRegistros; i *= 20)
            numRepeticoesGerais++;
    }

    for(int i = 0; i < 20 ; i++){ //iniciando as fitas de saída. variando de 21 até 40.
        sprintf(nomeArquivo, "fita%d.bin", i + 21);
        fitasSaida.fita[i] = fopen(nomeArquivo, "wb+");
    }

    for(int i = 0; i < numRepeticoesGerais; i++){
        if(i % 2 == 0)
            intercalaEntrada(fitasEntrada, fitasSaida, numRegistros, i + 1);
        else    
            intercalaSaida();
    }

    Aluno aluno;
    fseek(fitasSaida.fita[0], 0, SEEK_SET);
    for(int j = 0; j < 20; j++){
        for(int i = 0; i < 400; i++){
            if(fread(&aluno, sizeof(Aluno), 1, fitasSaida.fita[j]) != 1)
                break;
            printf("Indice: %d\n", i);
            printf("%s\n", aluno.cidade);
            printf("%s\n", aluno.curso);
            printf("%s\n", aluno.estado);
            printf("%ld\n", aluno.inscricao);
            printf("%lf\n\n", aluno.nota);
        }
        getchar();
        getchar();
    }

    for(int i = 0; i < 20; i++)
        fclose(fitasSaida.fita[i]);

    
}

void iniciaDadosEstrutura(EstruturaIntercalacao *vetor, int numeroFitas){
    for (int i = 0; i < numeroFitas; i++){
        vetor[i].aluno.cidade[0] = '\0';
        vetor[i].aluno.curso[0] = '\0';
        vetor[i].aluno.estado[0] = '\0';
        vetor[i].aluno.inscricao = 0;
        vetor[i].aluno.nota = 0;
        vetor[i].indice = 0;
    }
}

void intercalaEntrada(Fitas fitasEntrada, Fitas fitasSaida,int numRegistros, int qualRepeticao){


    if(numRegistros % 20 == 0){


        int itensPorBloco = pow(20, qualRepeticao);
        int numBlocos = numRegistros / itensPorBloco;
        int numFitas = 0;
        int fitaASerEscrita = 0;
        EstruturaIntercalacao vetorEstrutura[20];

        //A seguir ocorrem dois laços de repetição, resposáveis pela intercalação dos blocos das fitas. O for mais externo é responsável fazer a repetição ad intercalação para todas as colunas de blocos das fitas, já o for interno faz a intercalação propriamente dita.
        for(int i = numBlocos; i >= 20; i -= 20){ //for externo, repete intercalção pra toda coluna de blocos.
            if(i >= 20)
                numFitas = 20;
            else 
                numFitas = numBlocos;

            int indiceMenor = numFitas;
            int limiteFitasDisponiveis = numFitas;
            FILE *vetorAuxFitas[20];

            iniciaDadosEstrutura(vetorEstrutura, numFitas);

            for(int j = 0; j < numFitas; j++){
                fread(&vetorEstrutura[j].aluno, sizeof(Aluno), 1, fitasEntrada.fita[j]);
                vetorEstrutura[j].indice += 1;
                vetorAuxFitas[j] = fitasEntrada.fita[j]; 
            }

            for(int j = 0; j < (numFitas*(itensPorBloco - 1)); j++){
                //vou lendo e aumentando o indice de cada casa, quando um indice chegar ao máximo (itensPorBloco) eu passo essa fita para o final.
                indiceMenor = retornaMenor(vetorEstrutura, limiteFitasDisponiveis);
                fwrite(&vetorEstrutura[indiceMenor].aluno, sizeof(Aluno), 1, fitasSaida.fita[fitaASerEscrita]);
                vetorEstrutura[indiceMenor].indice += 1;
                if(fread(&vetorEstrutura[indiceMenor].aluno, sizeof(Aluno), 1, fitasEntrada.fita[indiceMenor])!=1 || vetorEstrutura[indiceMenor].indice == itensPorBloco){
                    FILE *temp = vetorAuxFitas[indiceMenor];
                    vetorAuxFitas[indiceMenor] = vetorAuxFitas[limiteFitasDisponiveis - 1];
                    vetorAuxFitas[limiteFitasDisponiveis - 1] = temp;
                    limiteFitasDisponiveis--;
                }
                if(limiteFitasDisponiveis == 0)
                    break;
            }
            fitaASerEscrita++;
            //return;
        }
    }
    else {
        //caso não seja um número inteiro só preciso verificar quantos porcento tem sobrando e ler isso da próxima fita.
    } 
        
}

void intercalaSaida(){
    printf("Saida\n");
}

int retornaMenor(EstruturaIntercalacao *vetor, int qtdItens){

    double menor = vetor[0].aluno.nota;
    int indiceMenor = 0;
    for(int i = 1; i < qtdItens; i++){
        if(vetor[i].aluno.nota < menor){
            menor = vetor[i].aluno.nota;
            indiceMenor = i;
        }
    }
    return indiceMenor;
}