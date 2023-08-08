#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "intercalacao.h"
#include "intercalaSub.h"
#include "ordenaInterno.h"
#include "Item.h"

void iniciaIntercalacaoSub(FILE *arq, int numReg, bool ArgOpcional){

    Fitas fitas;

    if(arq == NULL)
        return;

    //iniciando as fitas de entrada, lendo os dados e salvando nas respectivas fitas de destino.
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


    for(int i = 0; i < 40; i++){ //abertura das fitas de entrada, elas vão receber os valores do arquivo base.
        sprintf(nomeArquivo, "fita%d.bin", i + 1);
        fitas.fita[i] = fopen(nomeArquivo, "wb+");
    }
    
    TipoSub pivo[20];

    //Leitura inicial do pivo
    for(int x = 0; x < 20; x++){
        fread(&pivo[x].aluno, sizeof(Aluno), 1, arq);
        pivo[x].marcado = false;
    }

    int fitaASerEscrita = 0;
    int casasMarcadas = 0;
    int indiceMenor = 0;

    for(int j = 0; j < numReg - 20; j++){
        
        //Caso o pivo esteja todo marcado
        if(casasMarcadas == 20){
            for(int y = 0; y < 20; y++)
                pivo[y].marcado = false;
            
            casasMarcadas = 0;
            fitaASerEscrita++;
        }

        indiceMenor = retornaMenorSub(pivo);

        fwrite(&pivo[indiceMenor].aluno, sizeof(Aluno), 1, fitas.fita[fitaASerEscrita%20]);
        
        Aluno aux = pivo[indiceMenor].aluno;
        fread(&pivo[indiceMenor].aluno, sizeof(Aluno), 1, arq);
        
        if(pivo[indiceMenor].aluno.nota < aux.nota){
            pivo[indiceMenor].marcado = true;
            casasMarcadas++;
        }
    }

    intercalaSub(fitas, numReg, arqFinal);
}

int retornaMenorSub(TipoSub *vetor){
    Aluno menor = vetor[0].aluno;
    int indiceMenor = 0;

    if(vetor[0].marcado == true)
        menor.nota*=1000;

   /* for(int i = 0; i < 20; i++)
        printf("%.2lf ", vetor[i].aluno.nota);

    printf("\n\n");        
*/
    for(int i = 0; i < 20; i++){
        if(vetor[i].aluno.nota < menor.nota && vetor[i].marcado == false){
            menor.nota = vetor[i].aluno.nota;
            indiceMenor = i;
        }
    }
    
    return indiceMenor;
}

void intercalaSub(Fitas fitasEntrada, int numRegistros, FILE *arqFinal){

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
            intercalaEntradaSub(fitasEntrada, fitasSaida, numRegistros, i + 1);
        else    
            intercalaSaidaSub(fitasEntrada, fitasSaida, numRegistros, i + 1);
    }

    if(i - 1 % 2 == 0)
        salvaArqFinal(fitasSaida, arqFinal);
    else 
        salvaArqFinal(fitasEntrada, arqFinal);
    
    for(int x = 0; x < 20; x++)
        fclose(fitasSaida.fita[x]);
}

void intercalaEntradaSub(Fitas fitasEntrada, Fitas fitasSaida,int numRegistros, int qualRepeticao){
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
            
            indiceMenor = retornaMenor(vetorEstrutura, numFitas, itensPorBloco); //itens por bloco ItensBloco.qtd

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

void intercalaSaidaSub(Fitas fitasEntrada, Fitas fitasSaida,int numRegistros, int qualRepeticao){
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