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
