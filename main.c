#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "BibArquivos.h" // Biblioteca Professor Nilton
#include "tf_idf.h"

#define MAX_LENGTH 64

// variavel global
int error = 0;

int main(void){

    // área de declaração
    int escolha = 0;
    FILE *documento = NULL;
    FILE *Nota1 = NULL;
    FILE *Nota2 = NULL;
    FILE *Nota3 = NULL;
    FILE *Nota4 = NULL;
    FILE *Nota5 = NULL;
    //nome do documento utilizados no código
    char nome_documento[100];
    char palavra_lida[MAX_LENGTH];
    int length_palavra;
    //char vocabulario[4500][MAX_LENGTH];
    int tam = 0;

    //abertura dos arquivos notas
    Nota1 = fopen("files/Nota1.txt","a");
    Nota2 = fopen("files/Nota2.txt","a");
    Nota3 = fopen("files/Nota3.txt","a");
    Nota4 = fopen("files/Nota4.txt","a");
    Nota5 = fopen("files/Nota5.txt","a");
    //documento = fopen("tripadvisor_hotel_reviews.csv","r");

    //MENU

    while(escolha != 5)
    {
        printf("****************MENU******************\n");
        printf("1 - Ler o dataset do Trip Adivisor.\n");
        printf("2 - Gerar vocabulario.\n");
        printf("3 - Exibir TF-IDFs.\n");
        printf("4 - Exibir TF-IDF de uma Nota. Em ordem decrescente de valor de TF-IDF.\n");
        printf("5 - Sair\n");
        printf("*************************************\n");
        printf("Escolha :");
        scanf("%d",&escolha);

        //tripadvisor_hotel_reviews.csv

        //escolha do usuário
        if(escolha == 1){
            printf("Digite o diretorio com nome do documento:");
            scanf("%s",nome_documento);
            if(documento != NULL){
                fclose(documento);
            }
                        
            documento = Arquivo_AbreLeitura(nome_documento);
            //função para aglutinar textos nas Notas
            //está comentada para não sobrescrever os arquivos da pasta file
            //Os arquivos notas da pasta files estão prontos
            //se descomentar essa linha, antes de rodar de novo é preciso apagar os arquivos notas.
            //aglutina_texto(documento,Nota1,Nota2,Nota3,Nota4,Nota5,error);

            fclose(Nota1);
            //fclose(Nota2);
            //fclose(Nota3);
            //fclose(Nota4);
            //fclose(Nota5);

        }
        else if(escolha == 2)
        {
            printf("Escolha 2\n");
            Nota1 = fopen("files/Nota1.txt","r");
            //Nota2 = fopen("files/Nota2.txt","r");
            //Nota3 = fopen("files/Nota3.txt","r");
            //Nota4 = fopen("files/Nota4.txt","r");
            //Nota5 = fopen("files/Nota5.txt","r");
            int i = 0;
            while(!feof(Nota1))
            {
                //lê palavra por palavra
                fscanf(Nota1,"%s",palavra_lida);

                //calcula comprimento da palavra
                length_palavra = len(palavra_lida);

                //elimina pontuacao
                arranca_pontuacao(palavra_lida,&length_palavra);

                //elimina palavra com 3 character ou menos 
                if(length_palavra > 3){
                    printf("Palavra %d  comprimento %d : %s\n",i,length_palavra,palavra_lida);
                
                }

                i++;
            }
        }
        else if(escolha == 5){
            printf("Saindo...\n");
        }
        else{
            printf("Opcao ainda invalida\n");
            return 0;
        }
    }

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
