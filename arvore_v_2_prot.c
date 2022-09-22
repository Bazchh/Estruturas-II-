#include <stdio.h>
#include <stdlib.h>
#include "aluno.c"
#include <string.h>

struct no {
    Aluno dado;
    struct no *esq;
    struct no *dir;
};
//Escopo das funções
struct no *inserir(struct no *raiz, Aluno dados);
struct no *inserir_esq(struct no *raiz, Aluno dados);
struct no *inserir_dir(struct no *raiz, Aluno dados);
void ler_arquivo(FILE *arch, struct no *raiz);
void preordem(struct no *raiz);
void inordem(struct no *raiz);
void posordem(struct no *raiz);
void print(Aluno A);
void print_tree(struct no *raiz, char ordem[9]);

int main(){

    FILE *arch = fopen ("turma.dat","r");
    if (arch == NULL){
        printf("\nNão foi possivel abrir o arquivo");
    }
    struct no *raiz = 0;

    ler_arquivo(arch,raiz);
    char ordem[9];
    printf("\nInsira em qual ordem a raiz deve ser impressa: ");
    scanf("%s", ordem);
    print_tree(raiz, ordem);

}

struct no *novono(Aluno a){
    struct no* novo = (struct no*)malloc(sizeof(struct no));
           novo->dado = criaraluno2(a.nome, a.id, a.n1);
           novo->dir  = NULL;
           novo->esq  = NULL;
    return novo;
}

struct no *inserir(struct no *raiz, Aluno dados){
    if (raiz == NULL){
    raiz = novono(dados);
        }
    if(dados.id < raiz->dado.id){ //Primeira condição caso o conteudo inserido seja MEnOR que o valor do conteudo da raiz. Neste caso, os novos dados são inseridos a esquerda da arvore
      raiz->esq = inserir(raiz->esq, dados);
    }
        else if (dados.id > raiz->dado.id){ //Segunda condição caso o conteudo inserido seja MAIOR que o valor do conteudo da raiz. Neste caso, os novos dados são inseridos a direita da arvore
       raiz->dir = inserir(raiz->dir, dados); 
            }
     return raiz;
}  

void ler_arquivo(FILE *file, struct no *raiz){

    Aluno novo;
    nota n1;
    int mat;
    char nome[80];
   if(!file){
        printf("IMPOSSIVEL DE ABRIR");
    }
    while (!feof(file)){
        char *nome = (char*)malloc(sizeof(char)*80);
        fscanf(file, "%d %d %s",&n1, &mat, nome);
        novo = criaraluno2(nome, mat, n1);
        raiz = inserir(raiz, novo);

    }

    fclose(file);

}
void print(Aluno A) {
    printf("Id: %d\nNome: %s\nNota: %.2f\n\n", A.id, A.nome, A.n1);
}

void preordem(struct no *raiz) {
    if (raiz != 0) {
        print(raiz->dado);
    }
    if (raiz->esq != 0) {
        preordem(raiz->esq);
    }
    if (raiz->dir != 0) {
        preordem(raiz->dir);
    }
}

void inordem(struct no *raiz) {
    
    if (raiz->esq != 0) {
        inordem(raiz->esq);
    }
    if (raiz != 0) {
        print(raiz->dado);
    
    }
    if (raiz->dir != 0) {
        inordem(raiz->dir);
        }
}
void posordem(struct no *raiz) {
  
    if (raiz->esq != 0) {
        posordem(raiz->esq);

    }
    if (raiz->dir != 0) {
        posordem(raiz->dir);
    }  
    if (raiz != 0) {
        print(raiz->dado);
    }
}

void print_tree(struct no *raiz, char ordem[9]){
    if (strcmp(ordem,"preordem")){
        preordem(raiz);
    } else if (strcmp(ordem,"inordem")){
        inordem(raiz);
    } else if (strcmp(ordem,"posordem")){
        posordem(raiz);
    } else {
        printf("\nOpção escolhida é inválida");
    }
}
