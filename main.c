#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h> // tolower
#include <math.h> // log
#include "BibArquivos.h" // Biblioteca Professor Nilton
#include "tf_idf.h"

#define MAX_LENGTH 64
#define MAX_LENGTH_VECTOR 15

//############### INTEGRANTES ###################
// Luan Vasco Cavalcante - 190111836            //
// Leonardo Sampaio Barros - 170038971          //
// Vinícius Angelo de Brito Vieira - 190118059  //
// Os outros 2 integrantes deixaram a matéria   //
//################################################


// variavel global
int error = 0;
char palavra_lida[MAX_LENGTH];
int length_palavra;
int maior_comprimento;
int qtde_palavra;
int qntd_doc = 0;
int qntd_voc;
int lim;

int main(void){

    // área de declaração
    int escolha = 0;
    FILE *documento = NULL;
    FILE *Nota1 = NULL;
    FILE *Nota2 = NULL;
    FILE *Nota3 = NULL;
    FILE *Nota4 = NULL;
    FILE *Nota5 = NULL;
    FILE *vocabulario_sem_rep = NULL;
    FILE *vocabulario_rep = NULL;
    //nome do documento utilizados no código
    char nome_documento[100];
    //char palavra_vocabulario[MAX_LENGTH];

    //char vocabulario_vetor[50000][MAX_LENGTH_VECTOR];
    //int qtde_palavra = 0;
    int ehigual;


    //abertura dos arquivos notas
    Nota1 = fopen("files/Nota1.txt","a");
    Nota2 = fopen("files/Nota2.txt","a");
    Nota3 = fopen("files/Nota3.txt","a");
    Nota4 = fopen("files/Nota4.txt","a");
    Nota5 = fopen("files/Nota5.txt","a");

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

            fclose(documento);
            fclose(Nota1);
            fclose(Nota2);
            fclose(Nota3);
            fclose(Nota4);
            fclose(Nota5);

        }
        else if(escolha == 2)
        {
            vocabulario_rep = fopen("files/vocabulario_palavras.txt","w");
            vocabulario_sem_rep = fopen("files/voc_sem_rep.txt","w");
            maior_comprimento = 0;
            printf("Escolha 2\n");

            // reabrindo csv -- talvez nem precise reabrir, mas eu vou
            documento = Arquivo_AbreLeitura("tripadvisor_hotel_reviews.csv");

            // Função que gera vocabulario completo com repeticao !!
            gera_vocabulario_completo(documento,vocabulario_rep);

            fclose(vocabulario_rep);

            // agora vou abrir pra leitura
            vocabulario_rep = fopen("files/vocabulario_palavras.txt","r");


            printf("Quantas palavras deseja fazer o teste :");
            scanf("%d",&lim);
            gera_arq_sem_rep(vocabulario_sem_rep,vocabulario_rep,lim);

            // contar quantas palavras tem no txt

            // gerar o array de strings com [qntd_de_palavras][maior_len]
            fclose(vocabulario_sem_rep);
            //fclose(vocabulario_rep);
            fclose(documento);

            
        }
        else if(escolha == 3)
        {
            int aux = 0;
            int i = 0;

            FILE *nota1_palavras = NULL;
            FILE *nota2_palavras = NULL;
            FILE *nota3_palavras = NULL;
            FILE *nota4_palavras = NULL;
            FILE *nota5_palavras = NULL;
            vocabulario_sem_rep = fopen("files/voc_sem_rep.txt","r");

            nota1_palavras = fopen("files/nota1_palavras.txt","w");
            nota2_palavras = fopen("files/nota2_palavras.txt","w");
            nota3_palavras = fopen("files/nota3_palavras.txt","w");
            nota4_palavras = fopen("files/nota4_palavras.txt","w");
            nota5_palavras = fopen("files/nota5_palavras.txt","w");

            Nota1 = fopen("files/Nota1.txt","r");
            Nota2 = fopen("files/Nota2.txt","r");
            Nota3 = fopen("files/Nota3.txt","r");
            Nota4 = fopen("files/Nota4.txt","r");
            Nota5 = fopen("files/Nota5.txt","r");

            gera_vocabulario_completo(Nota1,nota1_palavras);
            gera_vocabulario_completo(Nota2,nota2_palavras);
            gera_vocabulario_completo(Nota3,nota3_palavras);
            gera_vocabulario_completo(Nota4,nota4_palavras);
            gera_vocabulario_completo(Nota5,nota5_palavras);

            fclose(nota1_palavras);
            fclose(nota2_palavras);
            fclose(nota3_palavras);
            fclose(nota4_palavras);
            fclose(nota5_palavras);
            
            nota1_palavras = fopen("files/nota1_palavras.txt","r");
            nota2_palavras = fopen("files/nota2_palavras.txt","r");
            nota3_palavras = fopen("files/nota3_palavras.txt","r");
            nota4_palavras = fopen("files/nota4_palavras.txt","r");
            nota5_palavras = fopen("files/nota5_palavras.txt","r");

            // conta quantas palavras tem em cada arquivo
            int qntd_palavras_N1 = len_arquivo(Nota1);
            int qntd_palavras_N2 = len_arquivo(Nota2);
            int qntd_palavras_N3 = len_arquivo(Nota3);
            int qntd_palavras_N4 = len_arquivo(Nota4);
            int qntd_palavras_N5 = len_arquivo(Nota5);

            // conta quantas palavras tem no vocabulário
            qntd_voc = len_arquivo(vocabulario_sem_rep);

            printf("####Quantidade de palavras : %d####\n",qntd_voc);

//################################################################################
            // declaração dos vetores dinâmicos
//################################################################################

            char vocabulario_vetor[qntd_voc][20];
            float TF_IDF_1[qntd_voc];
            float TF_IDF_2[qntd_voc];
            float TF_IDF_3[qntd_voc];
            float TF_IDF_4[qntd_voc];
            float TF_IDF_5[qntd_voc];
            float IDF[qntd_voc];

            //loop para gerar vetor de vocabulário
            rewind(vocabulario_sem_rep);

            while(!feof(vocabulario_sem_rep) && (aux < qntd_voc)){
                
                fscanf(vocabulario_sem_rep,"%s",palavra_lida);
                //printf("palavra arquivo %s\n",palavra_lida);
                strcpy(vocabulario_vetor[aux],palavra_lida);
                    //printf("palavra vetor %s\n",vocabulario_vetor[i]);
                aux++;
            }

            strcpy(vocabulario_vetor[0],"rice");

            // loop de verificação
            //for(aux = 0;aux<qntd_voc;aux++){
            //    printf("palavra %d : %s\n",aux,vocabulario_vetor[aux]);
            //}
            
            // IDF 
            int num_doc = 0;
            for(aux = 0;aux < qntd_voc;aux++)
            {
                //printf("Poorra onde tu tá ? \n");
                num_doc += acha_palavra_idf(nota1_palavras,vocabulario_vetor[aux]);
                num_doc += acha_palavra_idf(nota2_palavras,vocabulario_vetor[aux]);
                num_doc += acha_palavra_idf(nota3_palavras,vocabulario_vetor[aux]);
                num_doc += acha_palavra_idf(nota4_palavras,vocabulario_vetor[aux]);
                num_doc += acha_palavra_idf(nota5_palavras,vocabulario_vetor[aux]);
                
                //printf("num de vezes = %d\n",num_doc);

                IDF[aux] = log10f((float)5/(float)num_doc);

                //printf("%d - Para a palavra %s o IDF eh %f\n",aux,vocabulario_vetor[aux],IDF[aux]);

                num_doc = 0;
            }


            for(aux = 0;aux<qntd_voc;aux++){
                //printf("%d - palavra %s : %f\n",aux,vocabulario_vetor[aux],IDF[aux]);
            }

            // TFIDF PARA NOTA 1

            //printf("A qntd de vezes que  aparece eh %d\n",conta_palavra(nota1_palavras,"hotel"));
            //float teste = ((float)conta_palavra(nota1_palavras,vocabulario_vetor[1])/(float)qntd_palavras_N1) * IDF[40];
            //printf("\n\n\n%f\n\n\n\n",teste);

            //printf("\n\n####################%d##################\n\n",conta_palavra(nota1_palavras,"horrible"));

            for(aux = 0;aux < qntd_voc;aux++)
            {
                //printf("A qntd de vezes que %s aparece eh %d\n",vocabulario_vetor[aux],conta_palavra(nota1_palavras,vocabulario_vetor[aux]));

                //printf("IDF para %s = %f\n\n",vocabulario_vetor[aux],IDF[aux]);

                TF_IDF_1[aux] = 10000 * ((float)conta_palavra(nota1_palavras,vocabulario_vetor[aux])/(float)qntd_palavras_N1) * IDF[aux];
                TF_IDF_2[aux] = 10000 * ((float)conta_palavra(nota2_palavras,vocabulario_vetor[aux])/(float)qntd_palavras_N2) * IDF[aux];
                TF_IDF_3[aux] = 10000 * ((float)conta_palavra(nota3_palavras,vocabulario_vetor[aux])/(float)qntd_palavras_N3) * IDF[aux];
                TF_IDF_4[aux] = 10000 * ((float)conta_palavra(nota4_palavras,vocabulario_vetor[aux])/(float)qntd_palavras_N4) * IDF[aux];
                TF_IDF_5[aux] = 10000 * ((float)conta_palavra(nota5_palavras,vocabulario_vetor[aux])/(float)qntd_palavras_N5) * IDF[aux];
                
                //printf("tfidf 1 %f\n",TF_IDF_1[aux]);
                //printf("tfidf 2 %f\n",TF_IDF_2[aux]);
                //printf("tfidf 3 %f\n",TF_IDF_3[aux]);
                //printf("tfidf 4 %f\n",TF_IDF_4[aux]);
                //printf("tfidf 5 %f\n",TF_IDF_5[aux]);
                
            }

            //printf("Qntd de palavras:\nNota1 %d\nNota2 %d\nNota3 %d\nNota4 %d\nNota5 %d\n",
            //        qntd_palavras_N1,qntd_palavras_N2,qntd_palavras_N3,qntd_palavras_N4,qntd_palavras_N5);

            fclose(vocabulario_sem_rep);
            fclose(nota1_palavras);
            fclose(nota2_palavras);
            fclose(nota3_palavras);
            fclose(nota4_palavras);
            fclose(nota5_palavras);

            printf("|    Vocabulario     |   Nota 1     |    Nota 2    |     Nota 3   |    Nota 4     |     Nota 5     |\n");
            
            for(aux = 0; aux < qntd_voc ; aux++)
            {
                printf("|");
                printf("%s",vocabulario_vetor[aux]);
                for(int aux2 = 0;aux2 < 20 - len(vocabulario_vetor[aux]) ; aux2++)
                {
                    printf(" ");
                }

                printf("|   %f   |   %f   |   %f   |   %f    |    %f    |\n",TF_IDF_1[aux],TF_IDF_2[aux],TF_IDF_3[aux],TF_IDF_4[aux],TF_IDF_5[aux]);
            }
        }

        else if(escolha == 4)
        {
            printf("Não conseguimos fazer o vetor da opcao 3 chegar aqui na 4\n");
            printf("Se eu declarar como global não tem como alocar dinâmico");
        }
        else if(escolha == 5)
        {
            printf("Saindo...\n");
        }
        else{
            printf("Opcao ainda invalida\n");
        }
    }

    // numero de errors tem que permanecer em 0. por causa da primeira linha -1
    //printf("O NUMERO DE ERRORS EH : %d\n",error);

    // fechamento dos arquivos.
    //fclose(documento);
    fclose(Nota1);
    fclose(Nota2);
    fclose(Nota3);
    fclose(Nota4);
    fclose(Nota5);
    //
    //fclose(vocabulario_rep);

    //fclose(vocabulario);

	return 0;
}
