#include "Item.h"
//gera um arquivo binario bateado no PROVAO.TXT
int main(){
    FILE *arquivoTxt = fopen("PROVAO.TXT","r");
    if(arquivoTxt == NULL){
        printf("Nao foi possivel abrir o arquivo\n");
        return 0;
    }
    FILE *arquivoBin = fopen("PROVAO.bin","w+b");
    Aluno aluno;
    char lixo[20];
    int i = 0;
    while(i < 471706){
        fscanf(arquivoTxt, "%ld %lf", &aluno.inscricao, &aluno.nota);
        fgets(lixo, 2, arquivoTxt);
        fgets(aluno.estado, 3, arquivoTxt);
        fgets(lixo, 2, arquivoTxt);
        fgets(aluno.cidade, 50, arquivoTxt);
        fgets(lixo, 3, arquivoTxt);
        fgets(aluno.curso, 30, arquivoTxt);
        fgets(lixo, 3, arquivoTxt);
        fwrite(&aluno, sizeof(Aluno), 1, arquivoBin);
        i++;
    }

    fclose(arquivoBin);
    fclose(arquivoTxt);
    return 0;
}