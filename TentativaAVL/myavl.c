/* GRR20190372 & GRR20190367 */
/* jlvj19      &      vtvd19 */

#include <stdio.h>
#include <stdlib.h>

#include "libAVL.h"
#include "leitura.h"

int
main(void)
{   
    tNodo *raiz = NULL;
    
    /* Le o arquivo redirecionado para ao programa */
    raiz = lerEntrada(raiz); 

    /* Imprimi os nodos com sua chave e nivel separados por vírgula */
    profundidade(raiz,0);

    return EXIT_SUCCESS;
}