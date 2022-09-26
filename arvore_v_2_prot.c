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
void preordem(struct no *raiz);
void inordem(struct no *raiz);
void posordem(struct no *raiz);
void print(Aluno A);
void print_tree(struct no *raiz, char ordem[]);
void Ler_arch(char nome_arquivo[], struct no *raiz);
void search(struct no *raiz, Aluno a);

int main(){
    
struct no *raiz   = (struct no*)malloc(sizeof(struct no));

raiz->esq  = NULL;
raiz->dir  = NULL;
Aluno  *a = criaraluno("Mikael\0",72,7); //Insere a raiz
raiz->dado = *a;

char *arquivo = (char*)malloc(30*sizeof(char));

printf("\nQual o nome do arquivo a ser aberto: ");
scanf("%s", arquivo);

Ler_arch(arquivo, raiz);

char ordem[9];
printf("\nInsira a ordem que deseja imprimir: ");
scanf("%s", ordem);
print_tree(raiz,ordem);

Aluno a1; 
printf("\nInsira dados para serem buscados na arvore: ");
scanf(" %i %f %s", &a1.id, &a1.n1, a1.nome);

search(raiz, a1);
printf("\nDados encontrados: ");


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

void Ler_arch(char nome_arquivo[], struct no *raiz){

FILE *arch = fopen (nome_arquivo,"r");

    if (arch == NULL){
        printf("\nNão foi possivel abrir o arquivo");
    }
    
    Aluno aluno;

    float nota;
    int mat;
    char *name = (char*)malloc(30*sizeof(char));

while(!feof(arch)){
    fscanf(arch,"%f %i %s", &nota, &mat, name);
    aluno = criaraluno2(name,mat,nota);
    raiz = inserir(raiz,aluno);
}

fclose(arch);

}

void search(struct no *raiz, Aluno a){
    struct no *aux = novono(a);
    if (raiz = aux){
        Aluno R = aux->dado;
        return R;
    } else if(raiz != aux){
        if (raiz > aux){
            search(raiz->dir, a);
        }
    }

}
