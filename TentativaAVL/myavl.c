#include <stdio.h>
#include <stdlib.h>

#include "libAVL.h"
#include "leitura.h"

int
main(void)
{   
    tNodo *raiz = NULL;
    
    raiz = lerEntrada(raiz);
    nivel(raiz,0);
    return EXIT_SUCCESS;
}