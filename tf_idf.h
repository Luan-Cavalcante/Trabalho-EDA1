#ifndef TD_IDF_H
#define TD_IDF_H

#include <stdio.h>
#include <string.h>
#define MAX_LENGTH 64
char palavra_lida[MAX_LENGTH];
int length_palavra;
int maior_comprimento;
int qtde_palavra;


int acha_nota(char *);
void aglutina_texto(FILE *,FILE *Nota1,FILE *Nota2,FILE *Nota3,FILE *Nota4,FILE *Nota5,int);
int len(char *);
void arranca_pontuacao(char *,int *);
void normaliza_tolower(char *,int *);
int verifica_num(char *);
int procura_palavra(char *,int ,FILE *);
void gera_vocabulario_completo(FILE *,FILE *);
void gera_arq_sem_rep(FILE *,FILE *,int );
int len_arquivo(FILE *);
int conta_palavra(FILE *,char *);
int acha_palavra_idf(FILE *,char *);


#endif

//acha a nota recebendo uma frase lida com fgets
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
// cria o corpo textual com as 5 notas em arquivos diferentes
void aglutina_texto(FILE *documento,FILE *Nota1,FILE *Nota2,FILE *Nota3,FILE *Nota4,FILE *Nota5,int error)
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
// calcula o comprimento de uma string
int len(char *palavra){
    int i = 0;

    while(palavra[i] != 0){
        i++;
    }
    return i;
}
// arranca pontuação do inicio e do final de uma palavra
void arranca_pontuacao(char *palavra,int *len)
{
    int i = 0;
    int aux;
    //int tem_sinal = 0;
    char pontuacao[4] = {',','.','"'};


    for(i = 0;i < 3;i++){
        if(palavra[*len-1] == pontuacao[i]){
            //printf("tem pontuacao no fim\n");
            palavra[strlen(palavra) - 1] = palavra[strlen(palavra)];
            *len--;
        }
    }
    
    for(i = 0;i < 4;i++)
    {
        if(palavra[0] == pontuacao[i]){
            //printf("tem pontuacao no inicio\n");
            for(aux = 0 ; aux < *len ; aux++){
                palavra[aux] = palavra[aux+1];
            }
            *len--;
        }
    }
}
// passa a palavra pra minusculo
void normaliza_tolower(char * palavra,int *length){

    for(int i = 0; i<*length;i++){
        palavra[i] = tolower(palavra[i]);
    }

}
// verifica se a string lida começa com números
int verifica_num(char *palavra){

    char num[11] = {'0','1','2','3','4','5','6','7','8','9'};

    for(int i = 0 ; i < 11 ; i ++){
        if(palavra[0] == num[i])
        {
            //printf("tem numero\n");
            return 1;
        }
    }

    return 0;
}
// procura uma palavra no arquivo, usada no loop e guia ponteiros em mesmo arquivo
int procura_palavra(char *palavra,int qtde_palavra,FILE *arquivo){

    long int pos;
    rewind(arquivo);
    pos = ftell(arquivo);

    int qtde_palavra_ate_agora = 1;
    char palavra_lida2[MAX_LENGTH];


    while(qtde_palavra_ate_agora < qtde_palavra){

        fscanf(arquivo,"%s",palavra_lida2);
        pos = ftell(arquivo);
        //printf("\n*********FUNCAO*****************\nNo Loop %d posicao %ld\npalavra atual %d\n quero chegar em %d\n",qtde_palavra_ate_agora,pos,qtde_palavra_ate_agora,qtde_palavra);
        //printf("palavra %s eh igual a %s\n",palavra_lida2,palavra);
        if(strcmp(palavra,palavra_lida2) == 0)
        {
            //printf("\n\n************ACHEI\n%s eh igual %s\n\n",palavra,palavra_lida2);
            return 1;
        }
        qtde_palavra_ate_agora++;
    }
    return 0;
}
//printa em vocabulario 2 as palvras de documento
void gera_vocabulario_completo(FILE *documento,FILE *vocabulario2)
{
    //printa em vocabulario 2 as palvras de documento
    qtde_palavra = 0;
    while(!feof(documento))
    {   
        // ler palavra por palavra
        fscanf(documento,"%s",palavra_lida);
        
        // tratamento de palavra
        // len
        length_palavra = len(palavra_lida); 

        if(maior_comprimento < length_palavra){
            maior_comprimento = length_palavra;
        }

        // arranca pontuacao
        arranca_pontuacao(palavra_lida,&length_palavra);
        
        // tolower
        normaliza_tolower(palavra_lida,&length_palavra);

        //verifica num 
        // manda palavra pra função que verifica se eh repetida
        // TODO
        //printf("%s\n",palavra_lida);

        if(((length_palavra > 4) && (length_palavra <= 20)) && (verifica_num(palavra_lida) == 0)){
            //printf("EH PRA EU PRINTAR AGORA SHIT");
            fprintf(vocabulario2,"%s\n",palavra_lida);
            qtde_palavra++;
        }
    }

    printf("Maior comprimento de palavra: %d\nQntd de palavras = %d\n",maior_comprimento,qtde_palavra);
    
    // fechei pra mandar pro disco, shit !!!
    fclose(vocabulario2);
}
// gera arquivo sem repeticao , mas demora mtt !!!!!
void gera_arq_sem_rep(FILE *vocabulario,FILE *vocabulario2,int limite)
{

    long int posicao;
    long int qtde_palavra_lida = 0;
    int i = 0;

    while(1)
    {
        // li a palavra
        fscanf(vocabulario2,"%s",palavra_lida);
        //printf("palavra %s\n",palavra_lida);
        // peguei posicao 1 => 5  / 2 -> 12
        posicao = ftell(vocabulario2);

        i++;

        qtde_palavra_lida++;

        //printf("\n\n********MAIN*********\npalavra lida %s\nposicao %ld\nquantidade de palavra lida %d\n\n",palavra_lida,posicao,qtde_palavra_lida);

        if(qtde_palavra_lida == 1){
            printf("Printei a primeira palavra\n");
            fprintf(vocabulario,"%s\n",palavra_lida);

        }
        else{
            if(procura_palavra(palavra_lida,qtde_palavra_lida,vocabulario2) == 0){
                fprintf(vocabulario,"%s\n",palavra_lida);
                //printf("Printei %s pro arquivo\n",palavra_lida);
                rewind(vocabulario2);
            }
            fseek(vocabulario2,posicao,SEEK_SET);
        }

        //fclose(vocabulario);

        if(i==limite){
            break;
        }

        if((i % 1000) == 0){
            printf("Estou em %d mil\n",i);
        }
    }
}

int len_arquivo(FILE *arquivo)
{
    int i = 0;
    rewind(arquivo);

    while(!feof(arquivo)){
        fscanf(arquivo,"%s",palavra_lida);

        length_palavra = len(palavra_lida);

        if(maior_comprimento < length_palavra){
            maior_comprimento = length_palavra;
        }

        // arranca pontuacao
        arranca_pontuacao(palavra_lida,&length_palavra);

        // tolower
        normaliza_tolower(palavra_lida,&length_palavra);

        //verifica num e len
        if(((length_palavra > 4) && (length_palavra <= 20)) && (verifica_num(palavra_lida) == 0)){
            i++;
        }
        //printf("%s\n",palavra_lida);
    }
    // ele lê a última palavra 2 vezes
    return i;
}

int conta_palavra(FILE *nota,char *palavra)
{
    rewind(nota);
    int cont = 0;
    char word[64];
    //printf("Quero achar %s\n",palavra);

    while(!feof(nota))
    {
        fscanf(nota,"%s",word);

        if(strcmp(word,palavra) == 0)
        {
            cont++;
        }
    }

    return cont;
}

int acha_palavra_idf(FILE *arquivo,char *palavra)
{
    rewind(arquivo);
    char arroz[64];
    int i = 0;
    while(!feof(arquivo)){

        fscanf(arquivo,"%s",arroz);

        //printf("palavra lida %s palavra desejada %s\n",arroz,palavra);

        if(strcmp(arroz,palavra) == 0){
            //printf("Achei igual\n");
            //printf("%s eh igual a %s",arroz,palavra);
            return 1;
        }
    }
    return 0;
}
