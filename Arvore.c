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
struct no *raiz   = (struct no*)malloc(sizeof(struct no));
       raiz->esq  = NULL;
       raiz->dir  = NULL;
Aluno  *a         = criaraluno("Mikael\0",72,7);
       raiz->dado = *a;

}

void inserir(struct no *raiz, Aluno dados){
    struct no* novo   = (struct no*)malloc(sizeof(struct no));
           novo->dado = dados;
           novo->dir  = NULL;
           novo->esq  = NULL;
    
    if(novo->dado.id < raiz->dado.id){ //Primeira condição caso o conteudo inserido seja MENOR que o valor do conteudo da raiz. Neste caso, os novos dados são inseridos a esquerda da arvore
        if(raiz->esq = NULL){
            raiz->esq = novo;
        } else {
        struct no* pi;
        for(pi = raiz; pi->esq != NULL; pi = raiz->esq){
            pi->esq = novo;
            }
        }
    }
        else if (novo->dado.id > raiz->dado.id){ //Segunda condição caso o conteudo inserido seja MAIOR que o valor do conteudo da raiz. Neste caso, os novos dados são inseridos a direita da arvore
            if(raiz->dir = NULL){ //Caso o primeiro galho da arvore aponte para um ponteiro vazio, o novo conteudo será inserido neste mesmo espaço
            raiz->dir = novo;
            } else { //Caso contrario, andaremos pelos galhos até encontrar um espaço vazio onde será inserido os novos dados
                struct no* pi;
        for(pi = raiz; pi->dir != NULL; pi = raiz->dir){
            pi->dir = novo;
        }
            }
        }
     
}
