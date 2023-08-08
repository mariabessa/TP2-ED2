#include <stdio.h>
#include <stdlib.h>

void trocarBytes(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

void ordenarDescendente(char *nomeArquivo, int tamanhoRegistro) {
    FILE *arquivo = fopen(nomeArquivo, "rb+");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    fseek(arquivo, 0, SEEK_END);
    long tamanhoArquivo = ftell(arquivo);
    rewind(arquivo);

    char *registroA = (char *)malloc(tamanhoRegistro);
    char *registroB = (char *)malloc(tamanhoRegistro);

    long totalRegistros = tamanhoArquivo / tamanhoRegistro;
    for (long i = 0; i < totalRegistros / 2; i++) {
        fseek(arquivo, i * tamanhoRegistro, SEEK_SET);
        fread(registroA, tamanhoRegistro, 1, arquivo);

        fseek(arquivo, -((i + 1) * tamanhoRegistro), SEEK_END);
        fread(registroB, tamanhoRegistro, 1, arquivo);

        for (int j = 0; j < tamanhoRegistro; j++) {
            trocarBytes(&registroA[j], &registroB[j]);
        }

        fseek(arquivo, i * tamanhoRegistro, SEEK_SET);
        fwrite(registroB, tamanhoRegistro, 1, arquivo);

        fseek(arquivo, -((i + 1) * tamanhoRegistro), SEEK_END);
        fwrite(registroA, tamanhoRegistro, 1, arquivo);
    }

    free(registroA);
    free(registroB);
    fclose(arquivo);
}

int main() {
    char nomeArquivo[] = "dados.bin";
    int tamanhoRegistro = sizeof(int);

    ordenarDescendente(nomeArquivo, tamanhoRegistro);

    printf("Arquivo ordenado em ordem descendente.\n");

    return 0;
}