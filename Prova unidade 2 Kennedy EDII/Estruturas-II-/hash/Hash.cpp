#include "cidade.cpp"
#include "lerArquivos.cpp"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define SIZE 1024 //Tamanho para de posições da tabela hash
int divisao(dataItem *d, int n);
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

void init(hash &H, int n) {   //Função que inicia uma tabela hash e esvazia as posições da tabela
    for (int i = 0; i < n; i++) {
        H[i] = 0;
    }
}
void printHash(hash H){

for(int i = 0; i < SIZE; i++){
    printf("\n [%i] \nCEP: %i \nEstado: %s \n Cidade: %s", i+1,H[i]->city.id,H[i]->city.estado,H[i]->city.cidade);
    printf("\n ID: %i \n Latitude: %f \n Longitude: %f",H[i]->GPS.id, H[i]->GPS.la, H[i]->GPS.lo);
    printf("\n Key: %i\n", H[i]->key);
   }

}
int inserir(hash H, dataItem d, int (*funcHash)(dataItem *, int ), int cont) { //função que retorna um inteiro e recebe uma tabela hash, e um dos elementos do vetor de "dataItem"
// e uma função do tipo inteiro que tem como parametro uma variavel do tipo "dataItem" usada para escolher a posição (exemplos: metodo da multiplicação e da divisão)
    dataItem *aux = (dataItem *)malloc(sizeof(dataItem));
    *aux = d;
    int key = funcHash(aux, SIZE); //A key recebe o valor do resultado da função que foi passada
    dataItem *copy = (dataItem*)malloc(sizeof(dataItem)); //Criamos e alocamos esáço para uma variavel auxiliar para copiar os dados passados por parametro para o tipo "dataItem" 
    //passado na função 
    *copy = *aux; //Copiando dados para variavel auxiliar
    if (H[key] == 0) { //Caso a posição dada pelo calculo da função do metodo escolhido esteja vazia, o novo elemento é inserido na tabela hash
        H[key] = copy;
        return 0;
    } else if (H[key]!= 0){
        int i = 1;
       key = duplohash(aux,H,key, i,divisao);
       H[key] = copy;
    }
    return -1;
}

int remover(hash H, dataItem *d, int (*funcHash)(dataItem *, int )) { //Função que remove um elemento da tabela hash, recebe como parametro a tabela hash em si, um tipo "dataItem" e a função do metodo
//a ser utilizada para realizar a remoção. Essa função tem como parametro um tipo "dataItem"
    int key = funcHash(d,SIZE); //Recebe o valor retornado pela função do metodo escolhido (divisão ou multiplicação) 
    if (H[key] != 0) { //Caso a posição dada pelo calculo da função do metodo escolhido não esteja vazia, ela remove o elemento naquela posição
        dataItem *purge = H[key]; //Cria um tipo "dataItem" como ponteiro que aponta para a posição que está cheia e remover o elemento
        free (purge);
        // purge = 0;
        H[key] = 0; //Após remover o elemento, insere-se o valor 0, sinalizando "vazio" para aquela posição
        return 0;
    }
    return -1;
}

dataItem *buscar(hash H, int key, int (*funcHash)(dataItem *, int )){ //função que retorna um ponteiro do tipo "dataItem" e recebe como parametro a tabela hash, uma chave
// e a função do metodo escolhido para realizar a busca que tem como parametro um tipo "dataItem"
    dataItem *res = (dataItem*)malloc(sizeof(dataItem)); //Alocando e criando uma variavel do tipo "dataItem"
    res->key = key; //A variavel chave do tipo criado recebe a key que foi passada como parametro
    int pos = funcHash(res,SIZE); //Criamos uma variavel do tipo int para receber a posição buscado do elemento em questão que atribuimos o valor retornado pela função do metodo escolhido (multiplição ou divisão)
    res = H[pos]; //atribuimos o valor da posição encontrada e retornamos o valor com o mesmo armazenado na variavel do tipo "dataItem"
    return res;
}

int divisao(dataItem *d, int n) { //Função do metodo da divisão
    return d->key % n; //A função retorna o resto da chave, do elemento que vai ser inserido pelo tamanho da tabela (1024)
}

typedef unsigned long long int bigNumber;

int multiplicacao(dataItem *d, int n) {
    bigNumber key = (bigNumber)d->key;
    key *= key;
    int digits = ceil(log2((bigNumber)540000 * 540000));
    int signif = ceil(log2(SIZE - 1));
    int remover = digits - signif;
    int digitMask = (int)ceil(float(remover) / 2);
    bigNumber mask = ((SIZE-1) << digitMask);
    key = key & mask;
    key = (key >> digitMask);
    return key;
}

int hashCodeDobra(dataItem *d) {
    return d->key % SIZE;
}

int main() {
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
   inserir(H,aux,multiplicacao, i);
   i++;
    }

}
