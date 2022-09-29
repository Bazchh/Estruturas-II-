#include "aluno.c"
#include "arvore.c"

int main(){
    
struct no *raiz   = (struct no*)malloc(sizeof(struct no));

raiz->esq  = NULL;
raiz->dir  = NULL;
Aluno  *a = criaraluno("Mikael\0",72,7); //Insere a raiz
raiz->dado = *a;

char *arquivo = (char*)malloc(30*sizeof(char));

printf("\nQual o nome do arquivo a ser aberto: ");
scanf(" %s", arquivo);

raiz = Ler_arch(arquivo, raiz);

char ordem[9];
printf("\nInsira a ordem que deseja imprimir: ");
scanf(" %s", ordem);

print_tree(raiz,ordem);

int ID;

printf("\nInsira o ID a ser buscado: ");
scanf("%i", &ID);

struct no *res = search(raiz,ID);

}
