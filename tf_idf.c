#include "tf_idf.h"

int acha_nota(char *frase)
{

    int i = 0;
    int aspas = 0;
    char nota;
    int inota = 0;

    while(frase[i] != 0)
    {
        if(frase[i] == '"')
        {
            aspas++;
        }
        if(aspas == 2)
        {
            nota = frase[i+2];
                inota = nota - '0';
            break;
        }
        i++;
    }
    return inota;
}

void aglutina_texto(FILE *documento,FILE *Nota1,FILE *Nota2,FILE *Nota3,FILE *Nota4,FILE *Nota5)
{

    char frase[100000];
    int nota;

    while(fgets(frase,100000,documento) != NULL)
    {
        //puts(frase);


        //função para achar nota
        nota = acha_nota(frase);

        //printf("A nota do relato %d eh %d\n",i,nota);

        //classificação por notas para append no documento
        if(nota == 1){
            fputs(frase,Nota1);
        }
        else if(nota == 2){
            fputs(frase,Nota2);
        }
        else if(nota == 3){
            fputs(frase,Nota3);
        }
        else if(nota == 4){
            fputs(frase,Nota4);
        }
        else if(nota == 5){
            fputs(frase,Nota5);
        }
        else{
            error++;
        }
    }
}

int len(char *palavra){
    int i = 0;

    while(palavra[i] != 0){
        i++;
    }
    return i;
}


void arranca_pontuacao(char *palavra,int *len)
{
    int i = 0;
    int aux;
    //int tem_sinal = 0;
    char pontuacao[4] = {',','.','"'};


    for(i = 0;i < 4;i++){
        if(palavra[*len-1] == pontuacao[i]){
            palavra[strlen(palavra) - 1] = palavra[strlen(palavra)];
        }
    }
    
    for(i = 0;i < 4;i++)
    {
        if(palavra[0] == pontuacao[i]){
            for(aux = 0 ; aux < *len ; aux++){
                palavra[aux] = palavra[aux+1];
            }
            *len--;
        }
    }
}
