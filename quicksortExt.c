#include "quicksortExt.h"

void QuicksortExterno(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, int Esq, int Dir){
    int i, j;
    Pivo pivo; 
    // é para conferir se já tem o tamanho que caiba na memoria interna?
    if(Dir - Esq < 1) return;
    inicializaPivo(&pivo);
    particao(ArqLi, ArqEi, ArqLEs, pivo, Esq, Dir, &i, &j);
    QuicksortExterno(ArqLi, ArqEi, ArqLEs, Esq, i);
    QuicksortExterno(ArqLi, ArqEi, ArqLEs, j, Dir);
}

void particao(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, Pivo pivo, int Esq, int Dir, int *i, int *j){
    int Ls = Dir, Es = Dir, Li = Esq, Ei = Esq;
    double Linf = LIMITE_INF, Lsup = LIMITE_SUP;
    short ondeLer = TRUE;
    Aluno UltLido, escrita;
    fseek(*ArqLi, (Li - 1) * sizeof(Aluno), SEEK_SET);
    fseek(*ArqEi, (Ei - 1) * sizeof(Aluno), SEEK_SET);
    *i = Esq - 1;
    *j = Dir + 1;
    //o processo se encerra quando Ls e Li se cruzam
    while(Ls >= Li){
        if(pivo.n < MEMORIAMAX - 1){
            if(ondeLer) leSup(ArqLEs, &UltLido, &Ls, &ondeLer);
            else leInf(ArqLi, &UltLido, &Li, &ondeLer);
            inserirPivo(&pivo, UltLido);
            continue;
            if(Ls == Es) leSup(ArqLEs, &UltLido, &Ls, &ondeLer);
            else if (Li == Ei) leInf(ArqLi, &UltLido, &Li, &ondeLer);
            else if (ondeLer) leSup(ArqLEs, &UltLido, &Ls, &ondeLer);
            else leInf(ArqLi, &UltLido, &Li, &ondeLer);
            if(UltLido.nota > Lsup){
                *j = Es;
                escreveMax(ArqLEs, UltLido, &Es);
                continue;
            }
            else if(UltLido.nota < Linf){
                *i = Ei;
                escreveMin(ArqLi, UltLido, &Ei);
                continue;
            }
            inserirPivo(&pivo, &UltLido);
            if (Ei - Esq < Dir - Es){
                retiraMin(&pivo, &escrita);
                escreveMin(ArqLi, escrita, &Ei);
                Linf = escrita.nota;
            }
            else{
                retiraMax(&pivo, &escrita);
                escreveMax(ArqLEs, escrita, &Es);
                Lsup = escrita.nota;
            }
        }
    }
}

void inicializaPivo(Pivo *pivo){
    pivo->n = 0;    
}


void LeSup(FILE ***ArqLEs, Aluno *UltLido, int *Ls, short *OndeLer){
    fseek(*ArqLEs, (*Ls - 1) * sizeof(Aluno), SEEK_SET);
    fread(UltLido, sizeof(Aluno), 1, *ArqLEs);
    (*Ls)--;
    *OndeLer = FALSE;
}

void LeInf(FILE ***ArqLi, Aluno *UltLido, int *Li, short *OndeLer){
    fread(UltLido, sizeof(Aluno), Li, *ArqLi);
    (*Li)++;
    *OndeLer = TRUE;
}

void retiraMax(Pivo *pivo, Aluno *escrita){
    *escrita = pivo->vetor[pivo->n - 1];
    pivo->n--;
}

void retiraMin(Pivo *pivo, Aluno *escrita){
    *escrita = pivo->vetor[0];
    pivo->n--;
    for(int i = 0; i < pivo->n; i++){
        pivo->vetor[i] = pivo->vetor[i+1];
    }
}

void inserirPivo(Pivo *pivo, Aluno UltLido){
    int i = pivo->n;
    // arrasta todos os alunos com nota maior do que o UltLido para frente
    while(i > 0){
        if(UltLido.nota >= pivo->vetor[i-1].nota)
            break;
        pivo->vetor[i] = pivo->vetor[i-1];
        i--;
    }  
    // insere o Aluno de forma que o vetor continue ordenado
    pivo->vetor[i] = UltLido;
    pivo->n++;
}