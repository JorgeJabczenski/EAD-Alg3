#ifndef __AVL__
#define __AVL__

/* Constrói a estrutura de nodos */
struct nodo
{
    int chave;         // Chave do nodo
    struct nodo *esq;  // Filho da esquerda 
    struct nodo *dir;  // Filho da direita
    int fb;            // Fator de balanceamento
};

/*===Implementadas===*/
struct nodo *criaNodo(int chave);
struct nodo *insereNodo(struct nodo *n, int chave);

void preOrdem(struct nodo *n);
void emOrdem(struct nodo *n);
void posOrdem(struct nodo *n);
/*=== Para implementar ainda ===*/
/*
struct nodo *excluiNodo(int chave);
struct nodo *rotEsq(struct nodo *n);
struct nodo *rotDir(struct nodo *n);
struct nodo *min(struct nodo *n);
struct nodo *max(struct nodo *n);
struct nodo *sucessor(struct nodo *n);
int altura(struct nodo *n);
*/
#endif