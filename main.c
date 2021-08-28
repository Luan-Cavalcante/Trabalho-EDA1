#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "BibArquivos.h" // Biblioteca Professor Nilton
#include "tf_idf.h"

// variavel global
int error = 0;

int main(void){

    // área de declaração
    int escolha;
    FILE *documento = NULL;
    FILE *Nota1 = NULL;
    FILE *Nota2 = NULL;
    FILE *Nota3 = NULL;
    FILE *Nota4 = NULL;
    FILE *Nota5 = NULL;
    //nome do documento da escolha
    char nome_documento[100];

    //abertura dos arquivos notas
    Nota1 = fopen("files/Nota1.txt","a");
    Nota2 = fopen("files/Nota2.txt","a");
    Nota3 = fopen("files/Nota3.txt","a");
    Nota4 = fopen("files/Nota4.txt","a");
    Nota5 = fopen("files/Nota5.txt","a");
    //documento = fopen("tripadvisor_hotel_reviews.csv","r");

    //MENU

    printf("****************MENU******************\n");
    printf("1 - Ler o dataset do Trip Adivisor.\n");
    printf("2 - Gerar vocabulário.\n");
    printf("3 - Exibir TF-IDFs.\n");
    printf("4 - Exibir TF-IDF de uma Nota. Em ordem decrescente de valor de TF-IDF.\n");
    printf("5 - Sair\n");
    printf("*************************************\n");
    printf("Escolha :");
    scanf("%d",&escolha);

    //tripadvisor_hotel_reviews.csv

    //escolha do usuário
    if(escolha == 1){
        printf("Digite o diretório com nome do documento:");
        scanf("%s",nome_documento);
        if(documento != NULL)
                    fclose(documento);
                documento = Arquivo_AbreLeitura(nome_documento);
    }
    else{
        printf("Opção ainda invalida\n");
        return 0;
    }

    //função para aglutinar textos nas Notas
    //está comentada para não sobrescrever os arquivos da pasta file
    //Os arquivos notas da pasta files estão prontos
    //se descomentar essa linha, antes de rodar de novo é preciso apagar os arquivos notas.
    //aglutina_texto(documento,Nota1,Nota2,Nota3,Nota4,Nota5,error);

    // numero de errors tem que permanecer em 0. por causa da primeira linha -1
    printf("O NUMERO DE ERRORS EH : %d\n",error);


    // fechamento dos arquivos.

    fclose(documento);
    fclose(Nota1);
    fclose(Nota2);
    fclose(Nota3);
    fclose(Nota4);
    fclose(Nota5);

	return 0;
}
