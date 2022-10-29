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
void printHash(hash H);
int inserir(hash H, dataItem *d);
int remover(hash H, dataItem *d, int (*funcHash)(dataItem *, int ));
dataItem *buscar(hash H, int id);
int hash_modular(dataItem *d,int k);
int TabelaHash();;