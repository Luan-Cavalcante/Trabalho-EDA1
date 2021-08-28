//
//  BibArquivos.c
//  Arquivos
//
//  Created by Nilton Correia da Silva on 27/02/21.
//

#include "BibArquivos.h"
#include <stdlib.h> //necessário para malloc
#include <string.h> //necessário para strcpy


FILE *Arquivo_AbreLeitura(char *PNomeArquivo){
    return fopen(PNomeArquivo,"r");
}

FILE *Arquivo_Novo(char *PNomeArquivo){
    return fopen(PNomeArquivo,"w");
}


int Arquivo_MostraConteudo(FILE *parq){
    int c;
    if(parq == NULL)
        return 0; //Erro: ponteiro não apontado.
    while(1) {
       c = fgetc(parq);
       if( feof(parq) ) {
          break ;
       }
       printf("%c", c);
    }
    return 1;
}

int Arquivo_ProximaPalavra(FILE *parq, char *ppalavra){
    if(fscanf(parq, "%s", ppalavra) < 1){
        return 0;
    }
    return 1;
}
