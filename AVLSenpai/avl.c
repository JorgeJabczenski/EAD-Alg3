#include <stdio.h>
#include <stdlib.h>

typedef struct tNodo
{
	struct tNodo *esquerda;
	struct tNodo *direita;
	struct tNodo *pai;
	int chave;
	int altura;
} tNodo;
//------------------
tNodo 
*criarNodo(int chave)
{
	tNodo *nodo;
	nodo = (tNodo*) malloc (sizeof(tNodo));
	if (!nodo)
	{
		perror("Malloc do nodo falhou");
		exit(EXIT_FAILURE);
	}
	nodo->esquerda = NULL ;
	nodo->direita  = NULL ;
	nodo->pai      = NULL ;
	nodo->chave    = chave;
	nodo->altura   = 0;
	return nodo;
}
//------------------
void 
emOrdem(tNodo *nodo)
{
	if (nodo != NULL)
	{
		emOrdem(nodo->esquerda);
		printf("chave = %03d | ponteiro = %08x | pai = %08x | esquerda = %08x | direita = %08x | altura = %d\n", nodo->chave,nodo, nodo->pai,nodo->esquerda, nodo->direita, nodo->altura);
		emOrdem(nodo->direita);
	}
}
//------------------
// Altura
int 
altura(tNodo *nodo)
{
	int alturaDireita, alturaEsquerda;
	
	if (nodo == NULL)
		return -1;
	
	alturaDireita  = altura(nodo->direita);
	alturaEsquerda = altura(nodo->esquerda);

	if (alturaDireita > alturaEsquerda)
		return alturaDireita  + 1;
	else
		return alturaEsquerda + 1;
}
//------------------
// Balanceamento
int
balanceamento(tNodo *nodo)
{
	int balanco;

	if (nodo == NULL)
		return 0;
	return (altura(nodo->esquerda) - altura(nodo->direita));
}
//------------------
// Rotação Esquerda
tNodo
*rotacaoEsquerda(tNodo *nodo)
{
	int alturaDireita, alturaEsquerda;
	tNodo *temp;
	temp = nodo->direita;

	nodo->direita  = temp->esquerda; 
	temp->pai      = nodo->pai;
	nodo->pai      = temp;
	if (temp->esquerda != NULL)
		temp->esquerda->pai = nodo;
	temp->esquerda = nodo;

	// Arruma as alturas

	alturaDireita  = altura(nodo->direita);
	alturaEsquerda = altura(nodo->esquerda); 
	if (alturaDireita > alturaEsquerda)
		nodo->altura = alturaDireita + 1;
	else 
		nodo->altura = alturaEsquerda + 1;

	alturaDireita  = altura(temp->direita);
	alturaEsquerda = altura(temp->esquerda); 
	if (alturaDireita > alturaEsquerda)
		temp->altura = alturaDireita + 1;
	else 
		temp->altura = alturaEsquerda + 1;


	return temp;
}
//------------------
// Rotação Direita
tNodo
*rotacaoDireita(tNodo *nodo)
{
	int alturaDireita, alturaEsquerda;
	tNodo *temp;
	temp = nodo->esquerda;

	nodo->esquerda = temp->direita; 
	temp->pai      = nodo->pai;
	nodo->pai      = temp;
	if (temp->direita != NULL)
		temp->direita->pai = nodo;
	temp->direita  = nodo;
	
	// Arruma as alturas

	alturaDireita  = altura(nodo->direita);
	alturaEsquerda = altura(nodo->esquerda); 
	if (alturaDireita > alturaEsquerda)
		nodo->altura = alturaDireita + 1;
	else 
		nodo->altura = alturaEsquerda + 1;

	alturaDireita  = altura(temp->direita);
	alturaEsquerda = altura(temp->esquerda); 
	if (alturaDireita > alturaEsquerda)
		temp->altura = alturaDireita + 1;
	else 
		temp->altura = alturaEsquerda + 1;


	return temp;
}
//------------------REMODELAR
tNodo
*inserir(tNodo *nodo, int chave)
{
	int alturaDireita, alturaEsquerda, balanceamento;
	
	if (nodo == NULL)
		return criarNodo(chave);

	if (chave < nodo->chave)
	{
		nodo->esquerda = inserir(nodo->esquerda, chave);
		nodo->esquerda->pai = nodo;
	} else {
		nodo->direita  = inserir(nodo->direita,  chave);
		nodo->direita->pai = nodo;
	}

	alturaDireita  = altura(nodo->direita);
	alturaEsquerda = altura(nodo->esquerda); 
	
	if (alturaDireita > alturaEsquerda)
		nodo->altura = alturaDireita  + 1;
	else 
		nodo->altura = alturaEsquerda + 1;

	balanceamento = alturaEsquerda - alturaDireita;

	// Desbalanceado para a esquerda
	if (balanceamento >= 2)
	{
		if (chave > nodo->esquerda->chave) // Caiu no Zig Zap
			nodo->esquerda = rotacaoEsquerda(nodo->esquerda);
		return rotacaoDireita(nodo);
	}
	else if (balanceamento <= -2) // Desbalanceada para a direita
	{
		if (chave < nodo->direita->chave) // Caiu no Zig Zap	
			nodo->direita = rotacaoDireita(nodo->direita);
		return rotacaoEsquerda(nodo);
	}	

	return nodo;
}
//------------------
tNodo
*maximo(tNodo *nodo)
{
	if (nodo->direita == NULL)
		return nodo;
	else
		return maximo(nodo->direita);
}
//------------------
tNodo
*antecessor(tNodo *nodo)
{
	tNodo *nodoAntecessor = NULL;

	if (nodo->esquerda != NULL)
		return (maximo(nodo->esquerda));

	nodoAntecessor = nodo->pai;
	while(nodoAntecessor != NULL && nodo == nodoAntecessor->esquerda)
	{
		nodo = nodoAntecessor;
		nodoAntecessor = nodoAntecessor->pai;
	}

	return nodoAntecessor;
}
	
//------------------REMODELAR
tNodo 
*excluir(tNodo *nodo, int chave)
{
	
	// Não faz nada
	if (nodo == NULL)
		return nodo;
	// Caso a chave seja menor que a da raiz
	if (chave < nodo->chave)
		nodo->esquerda = excluir(nodo->esquerda, chave);

	// Caso seja maior	
	else if (chave > nodo->chave)
		nodo->direita  = excluir(nodo->direita,  chave);
	
	// ACHO QUE O PROBLEMA É AQUI
	// Achou o nodo que vai ser deletado
	else
	{
		if(nodo->esquerda == NULL || nodo->direita == NULL)
		{
			tNodo *temp = nodo->esquerda ? nodo->esquerda : nodo->direita;
			if (temp == NULL)
			{
				temp = nodo;
				nodo = NULL;
			}
			else
			{
				*nodo = *temp;
			}
			free(temp);
			
		} else {
			tNodo *temp = antecessor(nodo->esquerda);
			nodo->chave = temp->chave;
			nodo->esquerda = excluir(nodo->esquerda, temp->chave);
		}
	}

	// Caso a árvore só tivesse um nodo
	if(nodo == NULL)
		return nodo;

	nodo->altura = altura(nodo) + 1;

	int balanco = balanceamento(nodo);

	// Desbalanço para a Esquerda
	if (balanco >= 2)
	{
		if (balanceamento(nodo->esquerda) < 0)
			nodo->esquerda = rotacaoEsquerda(nodo->esquerda);
		return rotacaoDireita(nodo);
	} else 
	if (balanco <= -2)
	{
		if (balanceamento(nodo->direita) > 0)
			nodo->direita = rotacaoDireita(nodo->direita);
		return rotacaoEsquerda(nodo);
	}

	return nodo;
}
//------------------
int main(void)
{
	tNodo *raiz = NULL;

	/* Testa ZigZag */
	/*
	tNodo *raiz = criarNodo(50);
	inserir(raiz, 40);
	inserir(raiz, 60);
	inserir(raiz, 45);
	inserir(raiz, 43);
	emOrdem(raiz);
	putchar('\n');
	*/

	raiz = criarNodo(10);
	raiz = inserir(raiz,20);
	raiz = inserir(raiz,30);
	raiz = inserir(raiz,40);
	raiz = inserir(raiz,50);
	raiz = inserir(raiz,45);
	raiz = inserir(raiz,48);
	emOrdem(raiz);
	putchar('\n');
	
	printf("ALTURA RAIZ -> %d\n", altura(raiz));

	printf("EXCLUINDO 40\n");
	raiz = excluir(raiz, 40);
	emOrdem(raiz);
	putchar('\n');
	printf("EXCLUINDO 30\n");
	raiz = excluir(raiz, 30);
	emOrdem(raiz);
	putchar('\n');
	printf("EXCLUINDO 48\n");
	raiz = excluir(raiz, 48);
	emOrdem(raiz);
	putchar('\n');
	printf("EXCLUINDO 50\n");
	raiz = excluir(raiz, 50);
	emOrdem(raiz);
	putchar('\n');
	printf("EXCLUINDO 45\n");
	raiz = excluir(raiz,45);
	emOrdem(raiz);
	putchar('\n');
	/*
	printf("EXCLUINDO 15\n");
	excluir(raiz,15);
	emOrdem(raiz);
	putchar('\n');
	printf("EXCLUINDO 30\n");
	excluir(raiz,30);
	emOrdem(raiz);
	putchar('\n');
	printf("EXCLUINDO 45\n");
	excluir(raiz,45);
	emOrdem(raiz);
	putchar('\n');
	//printf("%d \n\n", raiz->esquerda->pai->direita->chave);
*/
	return 0;
}
