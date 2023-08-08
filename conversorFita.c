#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "intercalaSub.h"
#include "ordenaInterno.h"
#include "Item.h"

//gera um arquivo TXT baseado no arquivo bin que foi ordenado para controle se ordenação está correta
void converteFita(char fitaBin[20], int numeroFita) {
    Aluno aluno;
    char fitaTxt[20];

    snprintf(fitaTxt, sizeof(fitaTxt), "fita%d.txt", numeroFita);

    FILE *arquivoBin = fopen(fitaBin,"rb");
    FILE *arquivoTxt = fopen(fitaTxt, "w");

    if (arquivoBin == NULL) {
        printf("Erro ao abrir o arquivo binário.\n");
        return;
    }
    if (arquivoTxt == NULL) {
        printf("Erro ao abrir o arquivo de texto.\n");
        fclose(arquivoBin);
        return;
    }

    // Ler os registros de alunos do arquivo binário e transcrever para o arquivo de texto
    while (fread(&aluno, sizeof(Aluno), 1, arquivoBin) > 0) {
        fprintf(arquivoTxt, "%ld ", aluno.inscricao);
        fprintf(arquivoTxt, "%lf ", aluno.nota);
        fprintf(arquivoTxt, "%s ", aluno.cidade);
        fprintf(arquivoTxt, "%s ", aluno.estado);
        fprintf(arquivoTxt, "%s\n", aluno.curso);
    }

    // Fechar os arquivos
    fclose(arquivoBin);
    fclose(arquivoTxt);

    return;
}

void converteArquivo(char fitaBin[20], int numeroFita) {
    Aluno aluno;
    char fitaTxt[20];

    snprintf(fitaTxt, sizeof(fitaTxt), "fita%d.txt", numeroFita);

    FILE *arquivoBin = fopen(fitaBin,"rb");
    FILE *arquivoTxt = fopen(fitaTxt, "w");

    // Abrir o arquivo binário para leitura
    if (arquivoBin == NULL) {
        printf("Erro ao abrir o arquivo binário.\n");
        return;
    }
    // Abrir o arquivo de texto para escrita
    arquivoTxt = fopen("arqTeste.txt", "w");
    if (arquivoTxt == NULL) {
        printf("Erro ao abrir o arquivo de texto.\n");
        fclose(arquivoBin);
        return;
    }

    // Ler os registros de alunos do arquivo binário e transcrever para o arquivo de texto
    while (fread(&aluno, sizeof(Aluno), 1, arquivoBin) > 0) {
        fprintf(arquivoTxt, "Inscrição: %ld\n", aluno.inscricao);
        fprintf(arquivoTxt, "Nota: %.2f\n", aluno.nota);
        fprintf(arquivoTxt, "Estado: %s\n", aluno.estado);
        fprintf(arquivoTxt, "Cidade: %s\n", aluno.cidade);
        fprintf(arquivoTxt, "Curso: %s\n\n", aluno.curso);
    }

    // Fechar os arquivos
    fclose(arquivoBin);
    fclose(arquivoTxt);

    return;
}