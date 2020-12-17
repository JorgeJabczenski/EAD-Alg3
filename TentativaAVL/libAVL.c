#include <stdio.h>
#include <stdlib.h>
#include "libAVL.h"

//==================== CriarNodo  -> Aloca o espaço para um novo nodo ====================//
tNodo
*criarNodo(int chave)
{
    tNodo *nodo;
    // Cria um nodo e confere a sua alocação
    nodo = (tNodo*) malloc (sizeof(tNodo));
    if (nodo == NULL)
    {
        perror("Falha de MALLOC de um novo nodo");
        exit(EXIT_FAILURE);
    }

    // Atribui os valores padrão
    nodo->esquerda = NULL;
    nodo->direita  = NULL;
    nodo->chave    = chave;
    nodo->altura   = 0;

    return nodo;
}
//==================== emOrdem    -> Imprime os Valores das chaves em Ordem ====================//
void 
emOrdem(tNodo *nodo)
{
    if (nodo != NULL)
    {
        emOrdem(nodo->esquerda);
        printf("Chave = %03d | Pt = %08xu | Esq = %08x | Dir = %08x | H = %d |\n", nodo->chave, nodo, nodo->esquerda, nodo->direita, nodo->altura);
        emOrdem(nodo->direita);
    }
}
//==================== Nivel ====================//
void
nivel(tNodo *nodo, int n)
{
    if (nodo != NULL)
    {
        nivel(nodo->esquerda, n+1);
        printf("%d,%d\n", nodo->chave, n);
        nivel(nodo->direita , n+1);
    }
}
//==================== Maior      -> Devolve o maior entre dois inteiros ====================//
int 
maior(int a, int b)
{
    return (a > b) ? a : b;
}
//==================== Máximo     -> Devolve o maior nodo de uma árvore ====================//
tNodo
*maximo(tNodo *nodo)
{
    tNodo *temp = nodo;
    while(temp->direita != NULL)
        temp = temp->direita;
    return temp;
}
//==================== Altura     -> Calcula a altura do nodo, NULL vale -1 ====================//
int
altura(tNodo *nodo)
{
    if (nodo == NULL)
        return -1;
    return nodo->altura;
}
//==================== Fator de Balanceamento -> (Altura Esquerda - Altura Direita) ====================//
int 
fatorBalanceamento(tNodo *nodo)
{
    if (nodo == NULL)
        return 0;
    return (altura(nodo->esquerda) - altura(nodo->direita));
}
//==================== Rotação Esquerda ====================//
tNodo
*rotacaoEsquerda(tNodo *nodo)
{
    tNodo *temp = nodo->direita;

    /* Faz a troca dos ponteiros */
    nodo->direita = temp->esquerda;
    temp->esquerda = nodo;

    /* Ajusta a altura dos nodos rotacionados */
    nodo->altura = maior(altura(nodo->direita), altura(nodo->esquerda)) + 1;
    temp->altura = maior(altura(temp->direita), altura(temp->esquerda)) + 1;

    return temp;
}
//==================== Rotação Direita ====================//
tNodo
*rotacaoDireita(tNodo *nodo)
{
    tNodo *temp = nodo->esquerda;

    /* Faz a troca dos ponteiros */
    nodo->esquerda = temp->direita;
    temp->direita = nodo;

    /* Ajusta a altura dos nodos rotacionados */
    nodo->altura = maior(altura(nodo->direita), altura(nodo->esquerda)) + 1;
    temp->altura = maior(altura(temp->direita), altura(temp->esquerda)) + 1;

    return temp;
}
//==================== BalancearAVL -> Balanceia  a árvore ====================//
tNodo
*balancearAVL(tNodo *nodo)
{
    /* Arruma a altura dos nodos e o fator de balanceamento em seguida */
    nodo->altura = maior(altura(nodo->direita), altura(nodo->esquerda)) + 1;
    
    int fatorB = fatorBalanceamento(nodo);

    /* Desbalanceado para a Direita */
    if (fatorB == -2)
    {
        /* Direita-Esquerda (ZigZag) */
        if (fatorBalanceamento(nodo->direita) > 0)
            nodo->direita = rotacaoDireita(nodo->direita);
        /* Direita-Direita OU segundo passo da Direita-Esquerda */
        return rotacaoEsquerda(nodo);
    }

    /* Desbalanceado para a Esquerda */
    if (fatorB == 2)
    {
        /* Esquerda-Direita (ZigZag)*/
        if(fatorBalanceamento(nodo->esquerda) < 0)
            nodo->esquerda = rotacaoEsquerda(nodo->esquerda);
        /* Esquerda-Esquerda OU segundo passo da Esquerda-Direita */
        return rotacaoDireita(nodo);
    }
    return nodo;
}
//==================== Inserir     -> Insere um novo nodo ====================//
tNodo
*inserir(tNodo *nodo, int chave)
{
    /* Caso Base */
    if (nodo == NULL)
        return criarNodo(chave);
    
    /* Insere a chave de forma recursiva */
    if (chave < nodo->chave)
        nodo->esquerda = inserir(nodo->esquerda, chave);
    else 
        nodo->direita  = inserir(nodo->direita,  chave);

    return balancearAVL(nodo);
}
//==================== Antecessor -> Devolve o nodo antecessor ao nodo passado como argumento ====================//
tNodo 
*antecessor(tNodo *nodo)
{   if (nodo->esquerda != NULL)
        return(maximo(nodo->esquerda));
    return NULL;
}
//==================== Excluir    -> Exclui um nodo a partir de uma chave ====================//
tNodo
*excluir(tNodo *nodo, int chave)
{
    /* Caso Base */
    if (nodo == NULL)
        return nodo;

    /* Atua de forma semelhante a Incluir, fazendo o processo de forma recursiva */
    if (chave < nodo->chave)
        nodo->esquerda = excluir(nodo->esquerda, chave);
    else if (chave > nodo->chave)
        nodo->direita  = excluir(nodo->direita,  chave);
    else 
    {
        /* Apenas filho esquerdo ou nenhum filho */
        if (nodo->direita == NULL)
            return nodo->esquerda;
        /* Apenas filho direito  ou nenhum filho */
        else if (nodo->esquerda == NULL)
            return nodo->direita;
        /* Caso com dois filhos, substituir pelo antecessor */
        else 
        {
            tNodo *nodoAntecessor = antecessor(nodo);
            /* Substituir as chaves do nodo atual com o do Antecessor */
            nodo->chave = nodoAntecessor->chave;
            /* Excluir o Antecessor */
            nodo->esquerda = excluir(nodo->esquerda, nodoAntecessor->chave); 
        }
    }

    return balancearAVL(nodo);
}