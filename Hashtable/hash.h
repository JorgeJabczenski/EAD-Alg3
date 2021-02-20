#ifndef __HASH__
#define __HASH__

#include <stdio.h>
#include <stdlib.h>

#define M 11

typedef struct celula{
    int num;
    int excluido;
    int vazio;
} celula;

void inicializaVetor(celula* v, int t);

int h1(int k, int m);

int h2(int k, int m);

int busca(int n, celula *T1, celula *T2);

void inserir(int n, celula *T1, celula *T2);

void remover(int n, celula *T1, celula *T2);

void imprimir (celula *T1, celula *T2);

#endif