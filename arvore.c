#include <stdio.h>
#include "aluno.c"

struct no {
    Aluno dado;
    struct no *esq;
    struct no *dir;
};

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

void print(Aluno A) {
    printf("Id: %d\nNome: %s\nNota: %.1f\n\n", A.id, A.nome, A.n1);
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

void print_tree(struct no *raiz, char ordem[]){
    if (strcmp(ordem,"preordem") == 0){
        preordem(raiz);
    } else if (strcmp(ordem,"inordem") == 0){
        inordem(raiz);
    } else if (strcmp(ordem,"posordem") == 0){
        posordem(raiz);
    } else {
        printf("\nOpção escolhida é inválida");
    }
}

struct no *Ler_arch(char nome_arquivo[], struct no *raiz){

FILE *arch = fopen (nome_arquivo,"r");

    if (arch == NULL){
        printf("\nNão foi possivel abrir o arquivo");
    }
    
    Aluno aluno;

    float nota;
    int mat;
    

while(!feof(arch)){
    char *name = (char*)malloc(30*sizeof(char));
    fscanf(arch,"%f %i %s", &nota, &mat, name);
    aluno = criaraluno2(name,mat,nota);
    raiz = inserir(raiz,aluno);
}

fclose(arch);

return raiz;

}

struct no *search(struct no *raiz, int n){
   
    if(raiz == NULL){
        printf("\nA arvore esta vazia");
    }
    if (raiz->dado.id = n){
        
        Aluno r;
        r = raiz->dado;
        print(r);

    } else if(raiz->dado.id != n){
        if (raiz->dado.id > n){
            raiz = search(raiz->dir,n);
        } else if (raiz->dado.id < n){
            raiz = search(raiz->esq,n);
        }
    }
     return raiz;
}
