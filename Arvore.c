#include <stdio.h>
#include "aluno.c"

struct no {
    Aluno dado;
    struct no *esq;
    struct no *dir;
};

void inserir(struct no *raiz, Aluno dados);
void inserir_esq(struct no *raiz, Aluno dados, struct no *novo);
void inserir_dir(struct no *raiz, Aluno dados, struct no *novo);
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
      printf("\nQuantidade de elementos a serem inseridos na arvore: ");
      int n, i;
      scanf("%i", &n);
    for (i = 0; i < n; i++){
        printf("\nInsira o nome do aluno: ");
        scanf("%c", a->nome);
        printf("\nInsira a matricula do aluno: ");
        scanf("%i", &a->id);
        printf("\nInsira a nota do aluno: ");
        scanf("%f", &a->n1);
        a = criaraluno(a->nome,a->id, a->n1);
        inserir(raiz, *a);
    }

}

void inserir(struct no *raiz, Aluno dados){
    struct no* novo = (struct no*)malloc(sizeof(struct no));
           novo->dado = dados;
           novo->dir  = NULL;
           novo->esq  = NULL;
    
    if(novo->dado.id < raiz->dado.id){ //Primeira condição caso o conteudo inserido seja MENOR que o valor do conteudo da raiz. Neste caso, os novos dados são inseridos a esquerda da arvore
       inserir_esq(raiz, dados, novo);
    }
        else if (novo->dado.id > raiz->dado.id){ //Segunda condição caso o conteudo inserido seja MAIOR que o valor do conteudo da raiz. Neste caso, os novos dados são inseridos a direita da arvore
       inserir_dir(raiz, dados, novo); 
            }
     
}  

void inserir_esq(struct no *raiz, Aluno dados, struct no *novo){
    if(raiz->esq = NULL){
            raiz->esq = novo;
        } else {
        struct no* pi;
        for(pi = raiz; pi->esq != NULL; pi = raiz->esq){
            pi->esq = novo;
        }
    }
}

void inserir_dir(struct no *raiz, Aluno dados, struct no *novo){
    if(raiz->dir = NULL){ //Caso o primeiro galho da arvore aponte para um ponteiro vazio, o novo conteudo será inserido neste mesmo espaço
            raiz->dir = novo;
        } else { //Caso contrario, andaremos pelos galhos até encontrar um espaço vazio onde será inserido os novos dados
                struct no* pi;
        for(pi = raiz; pi->dir != NULL; pi = raiz->dir){
            pi->dir = novo;
        }
    }
}
