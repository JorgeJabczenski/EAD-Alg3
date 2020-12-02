#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

int
main()
{
    struct nodo *raiz = NULL;
    raiz = criaNodo(10);
    insereNodo(raiz,15);
    insereNodo(raiz,2);
    insereNodo(raiz,50);
    emOrdem(raiz);

    return EXIT_SUCCESS;
}

