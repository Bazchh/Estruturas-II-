#include "cidade.cpp"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define SIZE 1024 //Tamanho para de posições da tabela hash

typedef dataItem *hash[SIZE]; //Definindo um vetor de ponteiros de dataItem com nome de "hash"

void init(hash &H) {   //Função que inicia uma tabela hash e esvazia as posições da tabela
    for (int i = 0; i < SIZE; i++) {
        H[i] = 0;
    }
}
int inserir(hash H, dataItem *d, int (*funcHash)(dataItem *)) { //função que retorna um inteiro e recebe uma tabela hash, e um dos elementos do vetor de "dataItem"
// e uma função do tipo inteiro que tem como parametro uma variavel do tipo "dataItem" usada para escolher a posição (exemplos: metodo da multiplicação e da divisão)
    int key = funcHash(d); //A key recebe o valor do resultado da função que foi passada
    dataItem *copy = (dataItem*)malloc(sizeof(dataItem)); //Criamos e alocamos esáço para uma variavel auxiliar para copiar os dados passados por parametro para o tipo "dataItem" 
    //passado na função 
    *copy = *d; //Copiando dados para variavel auxiliar
    if (H[key] == 0) { //Caso a posição dada pelo calculo da função do metodo escolhido esteja vazia, o novo elemento é inserido na tabela hash
        H[key] = copy;
        return 0;
    }
    return -1;
}

int remover(hash H, dataItem *d, int (*funcHash)(dataItem *)) { //Função que remove um elemento da tabela hash, recebe como parametro a tabela hash em si, um tipo "dataItem" e a função do metodo
//a ser utilizada para realizar a remoção. Essa função tem como parametro um tipo "dataItem"
    int key = funcHash(d); //Recebe o valor retornado pela função do metodo escolhido (divisão ou multiplicação) 
    if (H[key] != 0) { //Caso a posição dada pelo calculo da função do metodo escolhido não esteja vazia, ela remove o elemento naquela posição
        dataItem *purge = H[key]; //Cria um tipo "dataItem" como ponteiro que aponta para a posição que está cheia e remover o elemento
        delete purge;
        // purge = 0;
        H[key] = 0; //Após remover o elemento, insere-se o valor 0, sinalizando "vazio" para aquela posição
        return 0;
    }
    return -1;
}

dataItem *buscar(hash H, int key, int (*funcHash)(dataItem *)){ //função que retorna um ponteiro do tipo "dataItem" e recebe como parametro a tabela hash, uma chave
// e a função do metodo escolhido para realizar a busca que tem como parametro um tipo "dataItem"
    dataItem *res = (dataItem*)malloc(sizeof(dataItem)); //Alocando e criando uma variavel do tipo "dataItem"
    res->key = key; //A variavel chave do tipo criado recebe a key que foi passada como parametro
    int pos = funcHash(res); //Criamos uma variavel do tipo int para receber a posição buscado do elemento em questão que atribuimos o valor retornado pela função do metodo escolhido (multiplição ou divisão)
    res = H[pos]; //atribuimos o valor da posição encontrada e retornamos o valor com o mesmo armazenado na variavel do tipo "dataItem"
    return res;
}

int divisao(dataItem *d) { //Função do metodo da divisão
    return d->key % SIZE; //A função retorna o resto da chave, do elemento que vai ser inserido pelo tamanho da tabela (1024)
}

typedef unsigned long long int bigNumber;

int multiplicacao(dataItem *d) {
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
    d->city.cidade = (char *)"Pau dos Ferros";
    d->city.id = 340940;
    d->city.estado = (char *)"RN";
    d->key = 340940;
    d->GPS.id = 340940;
    d->GPS.la = -6.11;
    d->GPS.lo = -38.2;

    int res = multiplicacao(d);
    hash H;
    init(H);

    inserir(H, d, divisao);

    // Não faz sentido mudar a função Hash, mas coloquei aqui para mostrar que é possível
    inserir(H, d, multiplicacao);
    remover(H, d, multiplicacao);
    inserir(H, d, multiplicacao);
    dataItem* dt = buscar(H, 340940, multiplicacao);
}
