#ifndef CIDADE_CPP
#define CIDADE_CPP
#define MAX 5570
#define SIZE 1024 
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <math.h>

typedef float latitude;
typedef float longitude;

struct cidade {
    unsigned int id;
    char *estado;
    char *cidade;
};

struct gps {
    unsigned int id;
    latitude la;
    longitude lo;
};

struct dataItem {
    int key;
    cidade city;
    gps GPS;
};

cidade *getCidades(char *arquivo) {
    FILE *f = fopen(arquivo, "r");
    cidade *cidades = (cidade *)malloc(MAX * sizeof(cidade));
    if (!f) {
        perror("Arquivo não existe");
        return NULL;
    }
    fscanf(f, "CODIGO MUNICIPIO;UF;NOME MUNICIPIO");
    unsigned int cod;
    char *uf;
    char *cid;
    int i = 0;
    while (!feof(f)) {
        uf = (char *)malloc(2 * sizeof(char));
        cid = (char *)malloc(40 * sizeof(char));
        fscanf(f, "%d %s ", &cod, uf);
        fgets(cid, 40 * sizeof(char), f);
       // printf("%d %s %s", cod, uf, cid);
        cidades[i].id = cod;
        cidades[i].estado = uf;
        cidades[i].cidade = cid;
        i = i + 1;
    }
    return cidades;
}

gps *getGps(char *localizacoes) {
    FILE *f = fopen(localizacoes, "r");
    gps *local = (gps *)malloc(MAX * sizeof(gps));
    if (!f) {
        perror("Arquivo não existe");
        return NULL;
    }
    fscanf(f, "CODIGO MUNICIPIO;LATITUDE;LONGITUDE");
    unsigned int cod;
    latitude la;
    longitude lo;
    int i = 0;
    while (!feof(f)) {
        fscanf(f, "%u;%f;%f", &cod, &la, &lo);
        //printf("%u;%.2f;%.2f\n", cod, la, lo);
        local[i].id = cod;
        local[i].la = la;
        local[i].lo = lo;
        i = i + 1;
    }
    return local;
}


void printDataItens(dataItem *dados) {
    for (int i = 0; i < MAX; i++) {
        printf("%d %d %s %.2f %.2f %s", i, dados[i].key, dados[i].city.estado, dados[i].GPS.la, dados[i].GPS.lo, dados[i].city.cidade);
    }
}

void saveDataItens(dataItem *dados){
    FILE *f = fopen("dados.dat", "w");
    for (int i = 0; i < MAX; i++) {
        fprintf(f, "%d %d %s %.2f %.2f %s", i, dados[i].key, dados[i].city.estado, dados[i].GPS.la, dados[i].GPS.lo, dados[i].city.cidade);
    }
}

dataItem *getItens(cidade *cities, gps *local) {
    dataItem *dados = (dataItem *)malloc(MAX * sizeof(dataItem));
    int k = 0;
    for (size_t i = 0; i < MAX; i++) {
        dados[k].key = cities[i].id;
        for (size_t j = 0; j < MAX; j++) {
            if (cities[i].id == local[j].id) {
                dados[k].city = cities[i];
                dados[k].GPS = local[j];
                k++;
            }
        }
    }
    return dados;
}

typedef dataItem *hash[SIZE]; //Definindo um vetor de ponteiros de dataItem com nome de "hash"

int duplohash(dataItem *d, hash H, int key, int i, int (*funchHash)(dataItem *, int )){
   int key2 = funchHash(d, SIZE-i) + 1;
    if(H[key2]!=0){
        key2 = (key+(i*key2))%SIZE;
    }
   if(H[key2] == 0){
    return key2;
   } else if(H[key2]!=0){
    i++;
    key2 = duplohash(d,H,key2,i,funchHash);
    
   }

 return key2;
}

typedef unsigned long long int bigNumber;

void init(hash &H, int n) {   
    for (int i = 0; i < n; i++) {
        H[i] = 0;
    }
}
int hash_modular(dataItem *d,int k){
    return ((d->key % SIZE)+k)%SIZE;
}
int inserir(hash H, dataItem d){
  int key, k, m, key_inicio;
  dataItem *copy = (dataItem*)malloc(sizeof(dataItem));
  *copy = d;
  k = 3;
  m = 0;
  key = hash_modular(copy,k);
  key_inicio = key;
   
  if(H[key] == 0){
        H[key] = copy;
        
        return key;
    }

 while(H[key] != 0){
    
    key = (((hash_modular(copy,k))%k)+k*((hash_modular(copy,m))+1))%SIZE;
    m++; 
    k++; 

    if(H[key] == 0){
        H[key] = copy;
        
        break; 
    }

    if(key == key_inicio){
        return -1;
    }

 }
  return key;
}

int remover(hash H, dataItem *d, int (*funcHash)(dataItem *, int )) {

    int key = funcHash(d,SIZE); 
    if (H[key] != 0) { 
        dataItem *purge = H[key]; 
        free (purge);
        H[key] = 0;
        return 0;
    }
    return -1;
}

dataItem *buscar(hash H, int id){ 
    dataItem *d = (dataItem*)malloc(sizeof(dataItem));
    d->key = id;

return d;    
}

void printHash(hash H){

    for(int i = 0; i < SIZE; i++){
    printf("\n ID: %i\n Estado: %s \n Cidade: %s Longitude: %.2f Latitude: %.2f\n\n",H[i]->key,H[i]->city.estado, H[i]->city.cidade,H[i]->GPS.lo,H[i]->GPS.la);
    }   
}

int TabelaHash() {
    dataItem *d = (dataItem *)malloc(sizeof(dataItem));
    hash H;
    init(H, SIZE);
    char *arquivo1 = (char*)"legenda.txt";
    char *arquivo2 = (char*)"coordenadas.csv";
   cidade *cidades = getCidades(arquivo1);
   gps *local = getGps(arquivo2);
   d = getItens(cidades,local);
   int i = 0;
   dataItem aux;
   while(i < SIZE){ 
   aux = d[i];
   inserir(H,aux);
   i++;
    }

 free(d);   
   /* printHash(H);

int id;

printf("Insira o ID a ser buscado na tabela Hash: ");
scanf("%i", &id);
*/

for(int i = 0; i < SIZE; i++){
printf("\n ID: %s\n\n",H[i]->city.cidade);
    } 

    return 0;
}

#endif
