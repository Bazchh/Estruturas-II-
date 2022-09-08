#include <stdio.h>
#include "aluno.c"

struct no {
    Aluno dado;
    struct no *esq;
    struct no *dir;
};
/*
typedef struct arvore{
    struct no *raiz;
}tree;
*/
int main(){
struct no *raiz = (struct no*)malloc(sizeof(struct no));
raiz->esq = NULL;
raiz->dir = NULL;
Aluno *a = criaraluno("Mikael\0",72,7);
raiz->dado = *a;

}

void inserir(struct no *raiz, Aluno dados){
    struct no* novo = (struct no*)malloc(sizeof(struct no));
    novo->dado = dados;
    novo->dir = NULL;
    novo->esq = NULL;
    if(novo->dado.id < raiz->dado.id){
        if(raiz->esq = NULL){
            raiz->esq = novo;    
        }
    } else {
        struct no* pi;
        for(pi = raiz; pi->esq != NULL; pi = raiz->esq){
            pi->esq = novo;
        }
    }
}
