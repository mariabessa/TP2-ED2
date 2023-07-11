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

    char tmp[100];
       
    int i = 0;
    while(i < 50){
        fscanf(arquivoTxt, "%ld %lf", &aluno.inscricao, &aluno.nota);
        fgets(tmp, 2, arquivoTxt);
        fgets(aluno.estado, 3, arquivoTxt);
        fgets(tmp, 2, arquivoTxt);
        fgets(aluno.cidade, 50, arquivoTxt);
        fgets(tmp, 3, arquivoTxt);
        fgets(aluno.curso, 30, arquivoTxt);
        fgets(tmp, 3, arquivoTxt);
        fwrite(&aluno, sizeof(Aluno), 1, arquivoBin);
        i++;
    }

    fclose(arquivoBin);
    fclose(arquivoTxt);
    return 0;
}