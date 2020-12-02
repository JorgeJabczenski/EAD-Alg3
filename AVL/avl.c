#include "avl.h"
#include <stdio.h>
#include <stdlib.h>

/* Cria um novo nodo */
struct nodo
*criaNodo(int chave)
{
    struct nodo *n;
    n = (struct nodo*) malloc(sizeof(struct nodo));
    if (!n){
        perror("Erro ao alocar um novo nodo");
        exit(1);
    }
    n->chave = chave;
    n->esq   = NULL;
    n->dir   = NULL;
    n->fb    = 0;
    return n;
}

/* Adaptar para uma AVL*/
struct nodo 
*insereNodo(struct nodo *n, int chave)
{
    if (n == NULL)
        return criaNodo(chave);
    
    if (chave < n->chave){
        n->esq = insereNodo(n->esq, chave);
    } else {
        n->dir = insereNodo(n->dir, chave);
    }
    return n;
}

void 
preOrdem(struct nodo *n)
{
    if (n != NULL){
        printf("%d ", n->chave);
        emOrdem(n->esq);
        emOrdem(n->dir);
    }
}

void 
emOrdem(struct nodo *n)
{
    if (n != NULL){
        emOrdem(n->esq);
        printf("%d ", n->chave);
        emOrdem(n->dir);
    }
}

void 
posOrdem(struct nodo *n)
{
    if (n != NULL){
        emOrdem(n->esq);
        emOrdem(n->dir);
        printf("%d ", n->chave);
    }
}