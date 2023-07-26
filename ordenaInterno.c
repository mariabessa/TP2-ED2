#include <stdio.h>
#include "Item.h"

void ordenaAlunos(Aluno *vetor, int tamanho){
    int gap, i, j;
    Aluno temp;
    
    // Definindo o tamanho do gap (intervalo)
    for (gap = tamanho / 2; gap > 0; gap /= 2) {
        for (i = gap; i < tamanho; i++) {
            temp.nota = vetor[i].nota;
            // Mover os elementos que estão antes do elemento atual
            // até onde eles devem estar na ordenação
            for (j = i; j >= gap && vetor[j - gap].nota > temp.nota; j -= gap) {
                vetor[j].nota = vetor[j - gap].nota;
            }
            vetor[j].nota = temp.nota;
        }
    }
}