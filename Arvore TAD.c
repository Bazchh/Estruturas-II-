#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"
#include "aluno.c"
#include <string.h>

struct no {
    Aluno dado;
    struct no *esq;
    struct no *dir;
};

int main(){
    
struct no *raiz   = (struct no*)malloc(sizeof(struct no));

raiz->esq  = NULL;
raiz->dir  = NULL;
Aluno  *a = criaraluno("Mikael\0",72,7); //Insere a raiz
raiz->dado = *a;

char *arquivo = (char*)malloc(30*sizeof(char));

printf("\nQual o nome do arquivo a ser aberto: ");
scanf(" %s", arquivo);

Ler_arch(arquivo, raiz);

char ordem[9];
printf("\nInsira a ordem que deseja imprimir: ");
scanf(" %s", ordem);

print_tree(raiz,ordem);

int ident;
printf("\nInsira o ID a ser buscado: ");
scanf("%i", &ident);

}
