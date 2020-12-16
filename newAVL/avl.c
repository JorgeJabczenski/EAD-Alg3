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
		printf("chave = %d \t| ponteiro = %08x \t| pai = %08x \t| esquerda = %08x \t| direita = %08x \t| altura = %d\n", nodo->chave,nodo, nodo->pai,nodo->esquerda, nodo->direita, nodo->altura);
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

	// Achou o nodo que vai ser deletado
	else
	{
		// Caso o nodo tenha apenas um dos filhos, tratar os dois casos
		if (nodo->esquerda == NULL)
		{
			tNodo *filhoDireita = nodo->direita;
			if (filhoDireita) 
				filhoDireita->pai = nodo->pai;
			free(nodo);
			return filhoDireita;
		}
		else if (nodo->direita == NULL) 
		{
			tNodo *filhoEsquerda = nodo->esquerda;
			//if (filhoEsquerda)
				filhoEsquerda->pai = nodo->pai;
			free(nodo);
			return filhoEsquerda;
		}
		// O nodo tem os dois filhos, substituir pelo antecessor
		else 
		{	tNodo *nodoAntecessor = antecessor(nodo);
			printf("Antecessor ao %d eh %d \n", nodo->chave, nodoAntecessor->chave);
			nodo->chave = nodoAntecessor->chave;
			nodo->esquerda = excluir(nodo->esquerda, nodo->chave);
		}
	}
	
	return nodo;
}
//------------------
int main(void)
{
	tNodo *raiz = criarNodo(50);	

	inserir(raiz,40);
	inserir(raiz,70);
	inserir(raiz,80);
	inserir(raiz,65);
	inserir(raiz,90);

	emOrdem(raiz);
	putchar('\n');
	
	printf("ALTURA RAIZ -> %d\n", altura(raiz));
/*
	printf("EXCLUINDO 10\n");
	excluir(raiz, 10);
	emOrdem(raiz);
	putchar('\n');
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
