#include "hash.h"

int 
main()
{
    celula T1[TAMMAX], T2[TAMMAX];
    char line[20];
    char op;
    int n;

    inicializaVetor(T1, TAMMAX);
    inicializaVetor(T2, TAMMAX);

    while(fgets(line, sizeof(line), stdin) != NULL) // Lê até o final da entrada, linha por linha
    {
        sscanf(line, "%c %d\n", &op,&n); // Separa da linha lida o operador e o número
        if (op == 'i') inserir(n, T1, T2);
        if (op == 'r') remover(n, T1, T2);
        imprimir(T1, T2);
    }


    return EXIT_SUCCESS;
}
