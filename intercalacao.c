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

    //A seguir temos o print de todos os registros de todos os blocos de todas as fitas (caso a quantidade de registros seja divisivel por 20).

    // Aluno aluno; 
    // for(int j = 0; j < numRegistros/20; j++){ //for de fitas
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

    //função pra passar arquivo .bin para .txt
    
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

    int i = 0;
    for(; i < numRepeticoesGerais; i++){

        for (int i = 0; i < 20; i++){
            fseek(fitasEntrada.fita[i], 0, SEEK_SET); //voltando pro início do arquivo de todas as fitas.
            fseek(fitasSaida.fita[i], 0, SEEK_SET);
        }

        if(i % 2 == 0)
            intercalaEntrada(fitasEntrada, fitasSaida, numRegistros, i + 1);
        else    
            intercalaSaida(fitasEntrada, fitasSaida, numRegistros, i + 1);
    }

    if(i - 1 % 2 == 0)
        salvaArqFinal(fitasSaida, arqFinal);
    else 
        salvaArqFinal(fitasEntrada, arqFinal);
    
    for(int x = 0; x < 20; x++)
        fclose(fitasSaida.fita[x]);
}

void iniciaDadosEstrutura(EstruturaIntercalacao *itemVetor, int numeroFitas){
    itemVetor->aluno.cidade[0] = '\0';
    itemVetor->aluno.curso[0] = '\0';
    itemVetor->aluno.estado[0] = '\0';
    itemVetor->aluno.inscricao = 0;
    itemVetor->aluno.nota = 0;
    itemVetor->indice = 0;
}

void intercalaEntrada(Fitas fitasEntrada, Fitas fitasSaida,int numRegistros, int qualRepeticao){
    int itensPorBloco = pow(20, qualRepeticao);
    if(numRegistros % itensPorBloco == 0){
        int numBlocos = numRegistros / itensPorBloco;
        int numFitas = 0;
        EstruturaIntercalacao vetorEstrutura[20];
        int fitaASerEscrita = 0;

        for(int i = 0; i < numBlocos; i += 20){
            if((numBlocos - i) >= 20)
                numFitas = 20;
            else 
                numFitas = numBlocos - i;

            bool intercalou = false;
            int indiceMenor = -1;

            for(int j = 0; j < numFitas; j++){
                iniciaDadosEstrutura(&vetorEstrutura[j], numFitas);
                fread(&vetorEstrutura[j].aluno, sizeof(Aluno), 1, fitasEntrada.fita[j]);
            }
            
            indiceMenor = retornaMenor(vetorEstrutura, numFitas, itensPorBloco);

            while(!intercalou){
                if(indiceMenor != -1){
                    fwrite(&vetorEstrutura[indiceMenor].aluno, sizeof(Aluno), 1, fitasSaida.fita[fitaASerEscrita % 20]);
                    vetorEstrutura[indiceMenor].indice++;
                    if(vetorEstrutura[indiceMenor].indice < itensPorBloco)
                        fread(&vetorEstrutura[indiceMenor].aluno, sizeof(Aluno), 1, fitasEntrada.fita[indiceMenor]);
                    indiceMenor = retornaMenor(vetorEstrutura, numFitas, itensPorBloco);
                }
                else 
                    intercalou = true;
            }
            fitaASerEscrita++;
        }
    }
    else {
        //caso não seja um número inteiro só preciso verificar quantos porcento tem sobrando e ler isso da próxima fita.
        int numBlocos = numRegistros / itensPorBloco;
        numBlocos += 1; //faço isto, pois o número de itens no último bloco será um número quebrado, mas ele deve ser lido\escrito, então adiciono 1 bloco a parte inteira.
        int numFitas = 0;
        EstruturaIntercalacao vetorEstrutura[20];
        int fitaASerEscrita = 0;
        //posso tentar ler o item, caso não tenha mais nada para ler, caso o fread retorne 0, faço o indice daquele item ser 20.

        for(int i = 0; i < numBlocos; i += 20){
            if((numBlocos - i) >= 20)
                numFitas = 20;
            else 
                numFitas = numBlocos - i;

            bool intercalou = false;
            int indiceMenor = -1;

            for(int j = 0; j < numFitas; j++){
                iniciaDadosEstrutura(&vetorEstrutura[j], numFitas);
                fread(&vetorEstrutura[j].aluno, sizeof(Aluno), 1, fitasEntrada.fita[j]);
            }
            
            indiceMenor = retornaMenor(vetorEstrutura, numFitas, itensPorBloco);

            while(!intercalou){
                if(indiceMenor != -1){
                    fwrite(&vetorEstrutura[indiceMenor].aluno, sizeof(Aluno), 1, fitasSaida.fita[fitaASerEscrita % 20]);
                    vetorEstrutura[indiceMenor].indice++;
                    if(vetorEstrutura[indiceMenor].indice < itensPorBloco)
                        if(fread(&vetorEstrutura[indiceMenor].aluno, sizeof(Aluno), 1, fitasEntrada.fita[indiceMenor]) != 1)
                            vetorEstrutura[indiceMenor].indice = itensPorBloco;
                    indiceMenor = retornaMenor(vetorEstrutura, numFitas, itensPorBloco);
                }
                else 
                    intercalou = true;
            }
            fitaASerEscrita++;
        }
    } 
        
}

void intercalaSaida(Fitas fitasEntrada, Fitas fitasSaida,int numRegistros, int qualRepeticao){
    int itensPorBloco = pow(20, qualRepeticao);
    if(numRegistros % itensPorBloco == 0){
        int numBlocos = numRegistros / itensPorBloco;
        int numFitas = 0;
        EstruturaIntercalacao vetorEstrutura[20];
        int fitaASerEscrita = 0;

        for(int i = 0; i < numBlocos; i += 20){
            if((numBlocos - i) >= 20)
                numFitas = 20;
            else 
                numFitas = numBlocos - i;
                
            bool intercalou = false;
            int indiceMenor = -1;

            for(int j = 0; j < numFitas; j++){
                iniciaDadosEstrutura(&vetorEstrutura[j], numFitas);
                fread(&vetorEstrutura[j].aluno, sizeof(Aluno), 1, fitasSaida.fita[j]);
            }
            
            indiceMenor = retornaMenor(vetorEstrutura, numFitas, itensPorBloco);

            while(!intercalou){
                if(indiceMenor != -1){
                    fwrite(&vetorEstrutura[indiceMenor].aluno, sizeof(Aluno), 1, fitasEntrada.fita[fitaASerEscrita % 20]);
                    vetorEstrutura[indiceMenor].indice++;
                    if(vetorEstrutura[indiceMenor].indice < itensPorBloco)
                        fread(&vetorEstrutura[indiceMenor].aluno, sizeof(Aluno), 1, fitasSaida.fita[indiceMenor]);
                    indiceMenor = retornaMenor(vetorEstrutura, numFitas, itensPorBloco);
                }
                else 
                    intercalou = true;
            }
            fitaASerEscrita++;
        }
    }
    else {
        //caso não seja um número inteiro só preciso verificar quantos porcento tem sobrando e ler isso da próxima fita.
        int numBlocos = numRegistros / itensPorBloco;
        numBlocos += 1; //faço isto, pois o número de itens no último bloco será um número quebrado, mas ele deve ser lido\escrito, então adiciono 1 bloco a parte inteira.
        int numFitas = 0;
        EstruturaIntercalacao vetorEstrutura[20];
        int fitaASerEscrita = 0;
        //posso tentar ler o item, caso não tenha mais nada para ler, caso o fread retorne 0, faço o indice daquele item ser 20.

        for(int i = 0; i < numBlocos; i += 20){
            if((numBlocos - i) >= 20)
                numFitas = 20;
            else 
                numFitas = numBlocos - i;
                
            bool intercalou = false;
            int indiceMenor = -1;

            for(int j = 0; j < numFitas; j++){
                iniciaDadosEstrutura(&vetorEstrutura[j], numFitas);
                fread(&vetorEstrutura[j].aluno, sizeof(Aluno), 1, fitasSaida.fita[j]);
            }
            
            indiceMenor = retornaMenor(vetorEstrutura, numFitas, itensPorBloco);

            while(!intercalou){
                if(indiceMenor != -1){
                    fwrite(&vetorEstrutura[indiceMenor].aluno, sizeof(Aluno), 1, fitasEntrada.fita[fitaASerEscrita % 20]);
                    vetorEstrutura[indiceMenor].indice++;
                    if(vetorEstrutura[indiceMenor].indice < itensPorBloco)
                        if(fread(&vetorEstrutura[indiceMenor].aluno, sizeof(Aluno), 1, fitasSaida.fita[indiceMenor]) != 1)
                            vetorEstrutura[indiceMenor].indice = itensPorBloco;
                    indiceMenor = retornaMenor(vetorEstrutura, numFitas, itensPorBloco);
                }
                else 
                    intercalou = true;
            }
            fitaASerEscrita++;
        }
    } 
}

int retornaMenor(EstruturaIntercalacao *vetor, int qtdItens, int itensPorBloco){
    double menor = 10001;
    int indiceMenor = -1;

    for(int i = 0; i < qtdItens; i++){
        if(vetor[i].indice < itensPorBloco)
            if(vetor[i].aluno.nota < menor){
                menor = vetor[i].aluno.nota;
                indiceMenor = i;
            }
    }

    return indiceMenor;
}

void salvaArqFinal(Fitas resultItercalacao, FILE *arqFinal){
    Aluno aluno;
    fseek(resultItercalacao.fita[0], 0, SEEK_SET);
    
    while(fread(&aluno, sizeof(Aluno), 1, resultItercalacao.fita[0]) == 1)
        fwrite(&aluno, sizeof(Aluno), 1, arqFinal);
}