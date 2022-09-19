#include <stdio.h>
#include "aluno.c"

struct no {
    Aluno dado;
    struct no *esq;
    struct no *dir;
};

struct no *inserir(struct no *raiz, Aluno dados);
struct no *inserir_esq(struct no *raiz, Aluno dados);
struct no *inserir_dir(struct no *raiz, Aluno dados);
/*
typedef struct arvore{
    struct no *raiz;
}tree;
*/
int main(){
struct no *raiz   = (struct no*)malloc(sizeof(struct no));
       raiz->esq  = NULL;
       raiz->dir  = NULL;
      Aluno  *a = criaraluno("Mikael\0",72,7); //Insere a raiz
       raiz->dado = *a;

}

struct no *NovoNo(Aluno a){
    struct no* novo = (struct no*)malloc(sizeof(struct no));
           novo->dado = criaraluno2(a.nome, a.id, a.n1);
           novo->dir  = NULL;
           novo->esq  = NULL;
    return novo;
}

struct no *inserir(struct no *raiz, Aluno dados){
    if (raiz == NULL){
    raiz = NovoNo(dados);
        }
    if(dados.id < raiz->dado.id){ //Primeira condição caso o conteudo inserido seja MENOR que o valor do conteudo da raiz. Neste caso, os novos dados são inseridos a esquerda da arvore
      raiz->esq = inserir_esq(raiz->esq, dados);
    }
        else if (dados.id > raiz->dado.id){ //Segunda condição caso o conteudo inserido seja MAIOR que o valor do conteudo da raiz. Neste caso, os novos dados são inseridos a direita da arvore
       raiz->dir = inserir_dir(raiz->dir, dados); 
            }
     return raiz;
}  

struct no *inserir_esq(struct no *raiz, Aluno dados){
    if(raiz->esq = NULL){
            raiz->esq->dado = dados;
        } else {
        struct no* pi;
        for(pi = raiz; pi->esq != NULL; pi = raiz->esq){
            pi->esq->dado = dados;
        }
    }
    return raiz;
}

struct no *inserir_dir(struct no *raiz, Aluno dados){
    if(raiz->dir = NULL){ //Caso o primeiro galho da arvore aponte para um ponteiro vazio, o novo conteudo será inserido neste mesmo espaço
            raiz->dir->dado = dados;
        } else { //Caso contrario, andaremos pelos galhos até encontrar um espaço vazio onde será inserido os novos dados
                struct no* pi;
        for(pi = raiz; pi->dir != NULL; pi = raiz->dir){
            pi->dir->dado = dados;
        }
    }

    return raiz;
}
