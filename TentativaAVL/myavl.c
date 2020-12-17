#include <stdio.h>
#include <stdlib.h>

#include "libAVL.h"
//==================== Main
int
main(void)
{   
    tNodo *raiz = NULL;
    
    raiz = inserir(raiz, 10);
    emOrdem(raiz);
    putchar('\n');

    raiz = inserir(raiz, 20);
    emOrdem(raiz);
    putchar('\n');

    raiz = inserir(raiz, 30);
    emOrdem(raiz);
    putchar('\n');

    raiz = inserir(raiz, 40);
    emOrdem(raiz);
    putchar('\n');

    raiz = inserir(raiz, 50);
    emOrdem(raiz);
    putchar('\n');

    raiz = inserir(raiz, 45);
    emOrdem(raiz);
    putchar('\n');

    raiz = inserir(raiz, 48);
    emOrdem(raiz);
    putchar('\n');

    raiz = excluir(raiz, 40);
    emOrdem(raiz);
    putchar('\n');

    raiz = inserir(raiz, 5);
    emOrdem(raiz);
    putchar('\n');

    raiz = inserir(raiz, 4);
    emOrdem(raiz);
    putchar('\n');

    raiz = inserir(raiz, 3);
    emOrdem(raiz);
    putchar('\n');

    raiz = excluir(raiz, 50);
    nivel(raiz,0);
    putchar('\n');

    return EXIT_SUCCESS;
}