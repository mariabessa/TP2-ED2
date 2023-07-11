#include "quicksortExt.h"

void quickSortInicia(int quantidade){
    FILE *ArqLEs, *ArqLi, *ArqEi;
    ArqLi = fopen("arquivo.txt", "r+");
    if(ArqLi == NULL){
        printf("Arquivo não pode ser aberto\n");
        return;
    }
    ArqEi = fopen("arquivo.txt", "r+");
    if(ArqEi == NULL){
        printf("Arquivo não pode ser aberto\n");
        return;
    }
    ArqLEs = fopen("arquivo.txt", "r+");
    if(ArqLEs == NULL){
        printf("Arquivo não pode ser aberto\n");
        return;
    }
    QuicksortExterno(&ArqLi, &ArqEi, &ArqLEs, 1, 5);
    fclose(ArqLi);
    fclose(ArqEi);
    fclose(ArqLEs);
    return;
}

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
    int Ls = Dir, Es = Dir, Li = Esq, Ei = Esq, Linf = INT_MIN, Lsup = INT_MAX;
    short ondeLer = 1;
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
        }
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
            escreveMin(ArqEi, UltLido, &Ei);
            continue;
        }
        inserirPivo(&pivo, UltLido);
        if (Ei - Esq < Dir - Es){
            retiraMin(&pivo, &escrita);
            escreveMin(ArqEi, escrita, &Ei);
            Linf = escrita.nota;
        }
        else{
            retiraMax(&pivo, &escrita);
            escreveMax(ArqLEs, escrita, &Es);
            Lsup = escrita.nota;
        }
    }while(Ei <= Es){
        retiraMin(&pivo, &escrita);
        escreveMin(ArqEi, escrita, &Ei);
    }
}


void inicializaPivo(Pivo *pivo){
    pivo->n = 0;    
}


void leSup(FILE **ArqLEs, Aluno *UltLido, int *Ls, short *OndeLer){
    fseek(*ArqLEs, (*Ls - 1) * sizeof(Aluno), SEEK_SET);
    fread(UltLido, sizeof(Aluno), 1, *ArqLEs);
    (*Ls)--;
    *OndeLer = 0;
}

void leInf(FILE **ArqLi, Aluno *UltLido, int *Li, short *OndeLer){
    fread(UltLido, sizeof(Aluno), 1, *ArqLi);
    (*Li)++;
    *OndeLer = 1;
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

void escreveMax(FILE **ArqLEs, Aluno aluno, int *Es){
    fseek(*ArqLEs, (*Es - 1) * sizeof(Aluno), SEEK_SET);
    fwrite(&aluno, sizeof(Aluno), 1, *ArqLEs);
    (*Es)--;
}

void escreveMin(FILE **ArqEi, Aluno aluno, int *Ei){
    fwrite(&aluno, sizeof(Aluno), 1, *ArqEi);
    (*Ei)++;
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