#include <stdio.h>
#include <stdlib.h>
#include "aluno.c"
#include <locale.h>

struct no {
    Aluno dado;
    struct no *esq;
    struct no *dir;
};
//Escopo das funções
struct no *inserir(struct no *raiz, Aluno dados);
struct no *inserir_esq(struct no *raiz, Aluno dados);
struct no *inserir_dir(struct no *raiz, Aluno dados);
void ler_arquivo(char arquivo[20], struct no *raiz);
void preordem(struct no *raiz);
void inordem(struct no *raiz);
void posordem(struct no *raiz);
void print(Aluno A);
void print_tree(struct no *raiz, char ordem[9]);

int main(){
setlocale(LC_ALL,"");
struct no *raiz   = (struct no*)malloc(sizeof(struct no));
       raiz->esq  = NULL;
       raiz->dir  = NULL;
      Aluno  *a = criaraluno("Mikael\0",72,7); //Insere a raiz
       raiz->dado = *a;
       char aux[20];
       int op;
       printf("\nInsira o nome do arquivo e o tipo de arquivo a ser lido: ");
       scanf("%s", aux);
       ler_arquivo(aux,raiz);

    printf("\nInsira em qual ordem a raiz deve ser impressa: ");
    scanf("%s", aux);
    print_tree(raiz,aux);

    while(op!= 2){
        printf("\nDeseja imprimir a raiz em outra ordem? ");
        scanf("%i", &op);
        if(op == 1){
        printf("\nInsira em qual ordem a raiz deve ser impressa: ");
        scanf("%s", aux);
        print_tree(raiz, aux);
        } 
    }
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

void ler_arquivo(char arquivo[20], struct no *raiz){
FILE *arch = fopen(arquivo,"r");
Aluno aux;

if(arch == NULL){
    printf("\n Não foi possivel abrir o arquivo");
}

int n1;
int id;
char n[30];
while(!feof(arch)){
    fscanf(arch,"%i %i %s", &n1, &id, n);
    aux.n1 = n1;
    aux.id = id;
    aux.nome = n;
    raiz = inserir(raiz,aux);
}

fclose(arch);

}
void print(Aluno A) {
    printf("Nome: %s\nNota: %i\nId: %i\n\n", A.nome, A.n1, A.id);
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
    if (ordem == "preordem"){
        preordem(raiz);
    } else if (ordem == "inordem"){
        inordem(raiz);
    } else if (ordem == "posordem"){
        posordem(raiz);
    } else {
        printf("\nOpção escolhida é inválida");
    }
}
