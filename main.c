#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "quicksortExt.h"
#include "intercalacao.h"

    
int main(int argc, char **argv){
    if (argc!=3 && argc!=4){
        printf("Número de argumentos inválido. As entradas são: <método> <quantidade> <situação> [-P](opcional)\n");
        return 0;
    }
    bool ArgOpcional = false;
    int opcode = atoi(argv[1]);
    int quantidade = atoi(argv[2]);
    int situacao = atoi(argv[3]);
    
    if(argc == 6 && strcmp(argv[5], "-p") == 0)
        ArgOpcional = true;

    /*  argv[1] = método - 1, 2 ou 3
        argv[2] = quantidade de registros
        argv[3] = situação (ordenado descententemente, ascendentemente ou desordenado aleatoriamente)
        argv[4](opcional) = [-P] colocado caso deseja que as chaves de pesquisa dos registros do arquivo considerado sejam apresentadas na tela
    */

    FILE *arq;
    if((arq = fopen("arquivo.txt", "r")) == NULL){
        printf("Erro ao abrir o arquivo\n");
    }


    //abertura do arquivo binário
    FILE *arquivo = fopen("PROVAO.bin","r+b");

    if(arquivo == NULL)
        printf("Não foi possível abrir o arquivo!!\n\n");

    //******************************  Intercalação balanceada de vários caminhos (2f fitas) com QuickSort interno ****************************** 
    else if (opcode == 1){ 
        iniciaItercalacao(arquivo, quantidade, ArgOpcional);
    }
    //******************************  Intercalação balanceada de vários caminhos (2f fitas) com Seleção por Substituição ****************************** 
    else if(opcode == 2){
    }
    //***********************************************************  QuickSort Externo *********************************************************** 
    else if (opcode == 3){
        quickSortInicia(quantidade, situacao);
    }
    fclose(arq);
    return 0;
}
