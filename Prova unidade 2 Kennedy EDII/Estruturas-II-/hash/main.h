#include "main.cpp"

struct cidade;
struct gps;
struct dataItem;
dataItem *getItens(cidade *, gps *);
void printDataItens(dataItem *);
void saveDataItens(dataItem *);
cidade *getCidades(char *arquivo);
gps *getGps(char *);
char* remover(char* text);
void init(hash &H, int n);
int divisao(dataItem *d, int n);
int multiplicacao(dataItem *d, int n);
int hashCodeDobra(dataItem *d);
void printHash(hash H);
int inserir(hash H, dataItem d, int (*funcHash)(dataItem *, int ), int cont);
int remover(hash H, dataItem *d, int (*funcHash)(dataItem *, int ));
dataItem *buscar(hash H, int key, int (*funcHash)(dataItem *, int ));
int duplohash(dataItem *d, hash H, int key, int i, int (*funchHash)(dataItem *, int ));
int TabelaHash();