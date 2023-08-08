#include "quicksortExt.h"

void quickSortInicia(int quantidade, int situacao){
    FILE *ArqLEs, *ArqLi, *ArqEi, *arquivo, *copia;
    //cria uma copia do arquivo para não perder o arquivo original
    Aluno aluno;
    // printf("%d\n", situacao);
    if (situacao == 1){
        arquivo = fopen("ascendente.bin", "rb");
        copia = fopen("ascendenteQS.bin", "wb");
        for (int i = 0; i < quantidade; i++){
            fread(&aluno, sizeof(Aluno), 1, arquivo);
            fwrite(&aluno, sizeof(Aluno), 1, copia);
        }
        // fread(aluno, sizeof(Aluno), quantidade, arquivo);
        // fwrite(aluno, sizeof(Aluno), quantidade, copia);
        ArqLEs = fopen("ascendenteQS.bin","r+b");
        ArqLi = fopen("ascendenteQS.bin","r+b");
        ArqEi = fopen("ascendenteQS.bin","r+b");
    }else if (situacao == 2){
        arquivo = fopen("descendente.bin", "rb");
        copia = fopen("descendenteQS.bin", "wb");
        for (int i = 0; i < quantidade; i++){
            fread(&aluno, sizeof(Aluno), 1, arquivo);
            fwrite(&aluno, sizeof(Aluno), 1, copia);
        }
        // fread(aluno, sizeof(Aluno), quantidade, arquivo);
        // fwrite(aluno, sizeof(Aluno), quantidade, copia);
        ArqLEs = fopen("descendenteQS.bin","r+b");
        ArqLi = fopen("descendenteQS.bin","r+b");
        ArqEi = fopen("descendenteQS.bin","r+b");
    }else if (situacao == 3){
        arquivo = fopen("PROVAO.bin", "rb");
        copia = fopen("aleatorioQS.bin", "wb");
        for (int i = 0; i < quantidade; i++){
            fread(&aluno, sizeof(Aluno), 1, arquivo);
            fwrite(&aluno, sizeof(Aluno), 1, copia);
        }
        // fread(aluno, sizeof(Aluno), quantidade, arquivo);
        // fwrite(aluno, sizeof(Aluno), quantidade, copia);
        ArqLEs = fopen("aleatorioQS.bin","r+b");
        ArqLi = fopen("aleatorioQS.bin","r+b");
        ArqEi = fopen("aleatorioQS.bin","r+b");
    }
    if(ArqLi == NULL || ArqEi == NULL || ArqLEs == NULL){
        // printf("Arquivo não pode ser aberto\n");
        return;
    }
    // ArqLi = fopen("PROVAO.bin", "r+b");
    // if(ArqLi == NULL){
    //     printf("Arquivo não pode ser aberto\n");
    //     return;
    // }
    // ArqEi = fopen("PROVAO.bin", "r+b");
    // if(ArqEi == NULL){
    //     printf("Arquivo não pode ser aberto\n");
    //     return;
    // }
    // ArqLEs = fopen("PROVAO.bin", "r+b");
    // if(ArqLEs == NULL){
    //     printf("Arquivo não pode ser aberto\n");
    //     return;
    // }
    QuicksortExterno(&ArqLi, &ArqEi, &ArqLEs, 1, quantidade);
    fclose(ArqLi);
    fclose(ArqEi);
    fclose(ArqLEs);
    fclose(arquivo);
    return;
}

void QuicksortExterno(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, int Esq, int Dir){
    int i, j;
    Pivo pivo; 
    // é para conferir se já tem o tamanho que caiba na memoria interna?
    if(Dir - Esq < 1) return;
    inicializaPivo(&pivo);
    particao(ArqLi, ArqEi, ArqLEs, pivo, Esq, Dir, &i, &j);
    fflush(*ArqLi);
    fflush(*ArqEi);
    fflush(*ArqLEs);
    QuicksortExterno(ArqLi, ArqEi, ArqLEs, Esq, i);
    QuicksortExterno(ArqLi, ArqEi, ArqLEs, j, Dir);
    // if(i - Esq < Dir - j){
    //     QuicksortExterno(ArqLi,ArqEi,ArqLEs,Esq,i);
    //     QuicksortExterno(ArqLi,ArqEi,ArqLEs,j,Dir);
    // }
    // else{
    //     QuicksortExterno(ArqLi,ArqEi,ArqLEs,j,Dir);
    //     QuicksortExterno(ArqLi,ArqEi,ArqLEs,Esq,i);
    // }    
}

void particao(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, Pivo pivo, int Esq, int Dir, int *i, int *j){
    int Ls = Dir, Es = Dir, Li = Esq, Ei = Esq, Linf = INT_MIN, Lsup = INT_MAX;
    short ondeLer = 1;
    Aluno UltLido, escrita;
    fseek(*ArqLi, (Li - 1) * sizeof(Aluno), SEEK_SET);
    fseek(*ArqEi, (Ei - 1) * sizeof(Aluno), SEEK_SET);
    *i = Esq - 1;
    *j = Dir + 1;
    //o processo se encerra quando Ls e Li se cruzam
    while(Ls >= Li){
        // printf("\npivo:\n");
        for(int k = 0; k < pivo.n; k++){
            printf("pivo[%d] = %lf\n", k, pivo.vetor[k].nota);
        }
        if(pivo.n < MEMORIAMAX - 1){
            if(ondeLer) leSup(ArqLEs, &UltLido, &Ls, &ondeLer);
            else leInf(ArqLi, &UltLido, &Li, &ondeLer);
            inserirPivo(&pivo, UltLido);
            continue;
        }
        if(Ls == Es) leSup(ArqLEs, &UltLido, &Ls, &ondeLer);
        else if (Li == Ei) leInf(ArqLi, &UltLido, &Li, &ondeLer);
        else if (ondeLer) leSup(ArqLEs, &UltLido, &Ls, &ondeLer);
        else leInf(ArqLi, &UltLido, &Li, &ondeLer);
        if(UltLido.nota > Lsup){
            // printf("\nprimeiro if\n");
            // printf("\n o j era = %d e foi para = %d\n", *j, Es);
            *j = Es;
            escreveMax(ArqLEs, UltLido, &Es);
            continue;
        }
        else if(UltLido.nota < Linf){
            // printf("\nsegundo if\n");
            *i = Ei;
            escreveMin(ArqEi, UltLido, &Ei);
            continue;
        }
        else if (Ei - Esq < Dir - Es){
            // printf("retira min\n");
            retiraMin(&pivo, &escrita);
            escreveMin(ArqEi, escrita, &Ei);
            Linf = escrita.nota;
        }else{
            // printf("retira max %d\n", pivo.n);
            retiraMax(&pivo, &escrita);
            escreveMax(ArqLEs, escrita, &Es);
            Lsup = escrita.nota;
        }
        inserirPivo(&pivo, UltLido);
    }



    while(Ei <= Es){
        retiraMin(&pivo, &escrita);
        escreveMin(ArqEi, escrita, &Ei);
    }
    // printa();
    // printf("\n\nvalor de i:%d\n\n", *i);
    // printf("\n\nvalor de j:%d\n\n", *j);
}


void inicializaPivo(Pivo *pivo){
    pivo->n = 0;    
}


void leSup(FILE **ArqLEs, Aluno *UltLido, int *Ls, short *OndeLer){
    fseek(*ArqLEs, (*Ls - 1) * sizeof(Aluno), SEEK_SET);
    fread(UltLido, sizeof(Aluno), 1, *ArqLEs);
    // printf("leu-se sup: %ld %lf\n", UltLido->inscricao, UltLido->nota);
    // printf("Ponteiro da leitura: %d", *Ls);
    (*Ls)--;
    *OndeLer = 0;
}

void leInf(FILE **ArqLi, Aluno *UltLido, int *Li, short *OndeLer){
    fread(UltLido, sizeof(Aluno), 1, *ArqLi);
    // printf("leu-se inf: %ld %lf\n", UltLido->inscricao, UltLido->nota);
    // printf("Ponteiro da leitura: %d", *Li);
    (*Li)++;
    *OndeLer = 1;
}

void retiraMax(Pivo *pivo, Aluno *escrita){
    *escrita = pivo->vetor[(pivo->n) - 1];
    pivo->n--;
}

void retiraMin(Pivo *pivo, Aluno *escrita){
    *escrita = pivo->vetor[0];
    pivo->n--;
    for(int i = 0; i < pivo->n; i++){
        pivo->vetor[i] = pivo->vetor[i+1];
    }
}

void escreveMax(FILE **ArqLEs, Aluno aluno, int *Es){
    // Aluno al;
    fseek(*ArqLEs, (*Es - 1) * sizeof(Aluno), SEEK_SET);
    fwrite(&aluno, sizeof(Aluno), 1, *ArqLEs);
    // printf("\nEscreveu na posição %d do arquivo o aluno de nota: %lf", *Es, aluno.nota);
    // fseek(*ArqLEs, (*Es - 1) * sizeof(Aluno), SEEK_SET);
    // fread(&al, sizeof(Aluno), 1, *ArqLEs);
    // printf("\nEscrita: %lf\n", al.nota);
    (*Es)--;
}

void escreveMin(FILE **ArqEi, Aluno aluno, int *Ei){
    // printf("\nEscreveu na posição %d do arquivo o aluno de nota: %lf", *Ei, aluno.nota);
    fwrite(&aluno, sizeof(Aluno), 1, *ArqEi);
    (*Ei)++;
}

void inserirPivo(Pivo *pivo, Aluno UltLido){
    int i = pivo->n - 1;
    while (i >= 0 && UltLido.nota < pivo->vetor[i].nota) {
        pivo->vetor[i + 1] = pivo->vetor[i];
        i--;
    }
    pivo->vetor[i + 1] = UltLido;
    pivo->n++;
}


// void printa(){
//     FILE *arquivoBin;
//     Aluno aluno;

//     // Abrir o arquivo binário para leitura
//     arquivoBin = fopen("PROVAO.bin", "rb");
//     if (arquivoBin == NULL) {
//         printf("Erro ao abrir o arquivo binário.\n");
//     }

//     // Ler os registros de alunos do arquivo binário e transcrever para o arquivo de texto
//     for(int i = 0; i < 15; i++){
//         fread(&aluno, sizeof(Aluno), 1, arquivoBin);
//         printf("nota[%d] = %lf\n", i, aluno.nota);
//     }
//     fclose(arquivoBin);
// }