/* GRR20190372 & GRR20190367 */
/* jlvj19      &      vtvd19 */

#include <stdio.h>
#include <stdlib.h>
#include "libAVL.h"
#include "leitura.h"

/* Le o arquivo redirecionado para ao programa */
tNodo 
*lerEntrada(tNodo *nodo)
{
    int n;   // Número que vai ser inserido ou removido
    char op; // Operação de inserção ou remoção
    char line[100];

    while(fgets(line, sizeof(line), stdin) != NULL) // Lê até o final da entrada, linha por linha
    {
        sscanf(line, "%c %d\n", &op,&n); // Separa da linha lida o operador e o número
        if (op == 'i') nodo = inserir(nodo, n);
        if (op == 'r') nodo = excluir(nodo, n);
    }
    return nodo;
}