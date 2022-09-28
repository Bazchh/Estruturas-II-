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

#endif
