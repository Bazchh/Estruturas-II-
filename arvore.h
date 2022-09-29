#include "aluno.c"

struct no *inserir(struct no *raiz, Aluno dados);
struct no *inserir_esq(struct no *raiz, Aluno dados);
struct no *inserir_dir(struct no *raiz, Aluno dados);
void preordem(struct no *raiz);
void inordem(struct no *raiz);
void posordem(struct no *raiz);
void print(Aluno A);
void print_tree(struct no *raiz, char ordem[]);
struct no *Ler_arch(char nome_arquivo[], struct no *raiz);
struct no *search(struct no *raiz, int n);