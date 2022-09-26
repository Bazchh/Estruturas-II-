#ifndef ALUNO_C
#define ALUNO_C
#include <stdio.h>
#include <stdlib.h>

typedef float nota; // Usado para quando mexermos muito com uma "variavel"
typedef unsigned int matricula;

 typedef struct aluno {
   const char *nome;
    matricula id;
    nota n1;
 }Aluno;

//ESCOPO DAS FUNÇÕES
Aluno* criaraluno(const char *string, matricula id, nota n);
Aluno criaraluno2(const char *string, matricula id, nota n);
/*
struct no {
    struct aluno dado;
    struct no *esq;
    struct no *dir;
};

typedef struct arvore{
    struct no *raiz;
}tree;
*/
Aluno* criaraluno(const char *string, matricula id, nota n){
    Aluno *novo = (Aluno*)malloc(sizeof(Aluno));
    novo->n1 = n;
    novo->id = id;
    novo->nome = string;
    return novo;
}
Aluno criaraluno2(const char *string, matricula id, nota n){
        Aluno novo;
    novo.n1 = n;
    novo.id = id;
    novo.nome = string;
    return novo;
}
/*
int main(){
    Aluno *a = criaraluno("Mikael\0", 10, 7);
    printf("\nNome: %s", a->nome);
    printf("\nMatricula: %i", a->id);
    printf("\nNota: %f", a->n1);
    return 0;

}

void menu (){
    printf("\n======Escolha uma opção======\n");
    printf("");
}*/

#endif
