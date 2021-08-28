//
//  BibArquivos.h
//  Arquivos
//
//  Created by Nilton Correia da Silva on 27/02/21.
//

#ifndef BibArquivos_h
#define BibArquivos_h

#include <stdio.h>

//Aberturas/criação de arquivos:
FILE *Arquivo_AbreLeitura(char *PNomeArquivo);
FILE *Arquivo_Novo(char *PNomeArquivo);


//Exibições de conteúdos de arquivos
int Arquivo_MostraConteudo(FILE *parq);
int Arquivo_ProximaPalavra(FILE *parq, char *ppalavra);


#endif /* BibArquivos_h */

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
