/* GRR20190372 & GRR20190367 */
/* jlvj19      &      vtvd19 */

#ifndef __LIBAVL__
#define __LIBAVL__

//==================== Define a Estrutura de Dados do tipo tNodo
typedef struct tNodo
{
    struct tNodo* esquerda;  // Nodo Filho da Esquerda
    struct tNodo* direita;   // Nodo Filho da Direita
    int chave;               // Valor da chave
    int altura;              // Altura do nodo
} tNodo;

tNodo *criarNodo(int chave);

void emOrdem(tNodo *nodo);

void profundidade(tNodo *nodo, int n);

int maior(int a, int b);

tNodo *maximo(tNodo *nodo);

int altura(tNodo *nodo);

int fatorBalanceamento(tNodo *nodo);

tNodo *rotacaoEsquerda(tNodo *nodo);

tNodo *rotacaoDireita(tNodo *nodo);

tNodo *balancearAVL(tNodo *nodo);

tNodo *inserir(tNodo *nodo, int chave);

tNodo *excluir(tNodo *nodo, int chave);

void excluiArvore(tNodo *nodo);

#endif