#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "intercalacao.h"
#include "ordenaInterno.h"
#include "Item.h"

void iniciaItercalacao(FILE *arq, int numReg, bool ArgOpcional){

    if(arq == NULL)
        return;

    //iniciando as fitas de entrada, lendo os dados e salvando nas respectivas fitas de destino.

    Fitas fitas;
    Aluno alunos[20]; 
    char nomeArquivo[10];
    int j = 0;
    int numeroFitas = 0;
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
                for(int y = 0; y <= j; y++)
                    fwrite(&alunos[y], sizeof(Aluno), 1, fitas.fita[indiceFita % 20]);
                numReg -= 20;
                indiceFita++;
                if(numeroFitas < 20)
                    numeroFitas++;
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
                for(int y = 0; y <= j; y++)
                    fwrite(&alunos[y], sizeof(Aluno), 1, fitas.fita[indiceFita % 20]);
                numReg -= 20;
                indiceFita++;
                if(numeroFitas < 20)
                    numeroFitas++;
            }
        }
    }
    else{
        int numBlocos = numReg/20;
        if(ArgOpcional){ //if usado para verficar se o usuário quer que os dados sejam printados ou não ([-P]).
            for(int i = 0; i < numBlocos; i++){
                //leitura dos vinte registros a serem organizados.
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
                for(int y = 0; y <= j; y++)
                    fwrite(&alunos[y], sizeof(Aluno), 1, fitas.fita[i % 20]);
                
                if(numeroFitas < 20)
                    numeroFitas++;
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
                
                if(numeroFitas < 20)
                    numeroFitas++;
            }
        }
    }

    for (int i = 0; i < 20; i++)
        fseek(fitas.fita[i], 0, SEEK_SET); //voltando pro início do arquivo de todas as fitas.
      
    intercala(fitas, numeroFitas, arqFinal);
    //funçãoparapassarbinparatxt
    fclose(arqFinal);
    
    
    //fechando os arquivos das fitas usadas
    for(int i = 0; i < 20; i++)
        fclose(fitas.fita[i]);
}

void intercala(Fitas fitasEntrada, int numeroFitas, FILE *arqFinal){

    EstruturaIntercalacao *vetor = (EstruturaIntercalacao*) malloc(sizeof(EstruturaIntercalacao) * numeroFitas); //vetor usado para intercalar os blocos das fitas, por isso é feita a alocação de memória com relação a quantidade de fitas contendo conteúdo. 
    Fitas fitasSaida; 
    char nomeArquivo[10];

    for(int i = 0; i < 20; i++){ //iniciando as fitas de saída. variando de 21 até 40.
        sprintf(nomeArquivo, "fita%d.bin", i + 21);
        fitasSaida.fita[i] = fopen(nomeArquivo, "wb+");
    }

    // for(;;){
    //     for(int i = 0; i < numeroFitas; i++){
    //         if(fread(&alunos[j], sizeof(Aluno), 1, arq) != 1)
    //             break;
    //     }
    // }

    printf("saiu\n");

    for(int i = 0; i < 20; i++)
        fclose(fitasSaida.fita[i]);

    free(vetor);
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
//acho que vou ter que fazer uma função para reiniciar os dados da EstruturaIntercalção. Explicação: Caso sejam lidos 20 blocos e hajam mais de 20 blocos, o processo vai ter que recomeçar para os blocos excedentes das fitas.

//as fitas vão para o final caso o índice da estrutura chegue a 20 ou caso o arquivo da fita chegue ao final.