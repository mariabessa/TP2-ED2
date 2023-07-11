#include <stdio.h>
#include "Item.h"

int main() {
    FILE *arquivo;
    Aluno aluno;

    // Abrir o arquivo para escrita
    arquivo = fopen("arquivoTeste.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Solicitar dados ao usuário
    for(int i = 0; i < 10; i++){
        printf("Digite os dados: \n");
        fgets(&aluno, sizeof(Aluno), stdin);
        fwrite(&aluno ,sizeof(Aluno), 1, arquivo);
    }
    // Escrever os dados no arquivo

    // Fechar o arquivo
    fclose(arquivo);

    printf("Dados gravados com sucesso no arquivo.\n");

    return 0;
}