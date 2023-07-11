#include "Item.h"

//gera um arquivo TXT baseado no arquivo bin que foi ordenado para controle se ordenação está correta
int main() {
    FILE *arquivoBin, *arquivoTxt;
    Aluno aluno;

    // Abrir o arquivo binário para leitura
    arquivoBin = fopen("PROVAO.bin", "rb");
    if (arquivoBin == NULL) {
        printf("Erro ao abrir o arquivo binário.\n");
        return 1;
    }
    // Abrir o arquivo de texto para escrita
    arquivoTxt = fopen("arqTeste.txt", "w");
    if (arquivoTxt == NULL) {
        printf("Erro ao abrir o arquivo de texto.\n");
        fclose(arquivoBin);
        return 1;
    }

    // Ler os registros de alunos do arquivo binário e transcrever para o arquivo de texto
    while (fread(&aluno, sizeof(Aluno), 1, arquivoBin) > 0) {
        fprintf(arquivoTxt, "Inscrição: %ld\n", aluno.inscricao);
        fprintf(arquivoTxt, "Nota: %.2f\n", aluno.nota);
        fprintf(arquivoTxt, "Estado: %s\n", aluno.estado);
        fprintf(arquivoTxt, "Cidade: %s\n", aluno.cidade);
        fprintf(arquivoTxt, "Curso: %s\n\n", aluno.curso);
        printf("%ld %lf %s %s %s\n", aluno.inscricao, aluno.nota, aluno.cidade, aluno.estado, aluno.curso);
    }

    // Fechar os arquivos
    fclose(arquivoBin);
    fclose(arquivoTxt);

    printf("Transcrição concluída com sucesso.\n");

    return 0;
}
