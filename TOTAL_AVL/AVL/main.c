#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

int
main(void)
{
    char op; // Operação de inserção ou remoção
    int n;   // Número que vai ser inserido ou removido
    static char line[100];

    struct nodo *raiz = NULL; // Criação da raiz da árvore;

    scanf("%c %d\n", &op, &n);
    raiz = criaNodo(n);

    while(fgets(line, sizeof(line), stdin) != NULL) // Lê até o final da entrada, linha por linha
    {
        sscanf(line, "%c %d\n", &op,&n); // Separa da linha lida o operador e o número
        if (op == 'i') insereNodo(raiz, n);
    }
/*
    insereNodo(raiz,15);
    insereNodo(raiz,2);
    insereNodo(raiz,50);
*/

    emOrdem(raiz);
    putchar('\n');

    return EXIT_SUCCESS;
}