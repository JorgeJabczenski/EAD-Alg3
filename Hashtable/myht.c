#include <stdio.h>
#include <stdlib.h>

#define TAMMAX 11
#define M      11


typedef struct celula{
    int num;
    int excluido;
    int vazia;
} celula;


void 
inicializaVetor(celula* v, int t)
{
    for (int i = 0; i < t; i++)
    {
        v[i].excluido = 0;
        v[i].vazia    = 1;
    }
}

/************************/
/*  FUNÇÕES DE HASHING  */
int 
h1(int k, int m)
{
    return k % m;
}

int
h2(int k, int m)
{
    return (int) (m*(k*0.9 - (int)(k*0.9)));
}
/************************/


void 
inserir(int n, celula *T1, celula *T2)
{
    int pos1, pos2;

    pos1 = h1(n, M);~
    pos2 = h2(n,M);   /* FEIO , NAO FAZER ISSO, RETIRAR DEPOIS, SÉRIO */

    if (T1[pos1].vazia == 1 || (T1[pos1].excluido == 1))
    {
        T1[pos1].num = n;
        T1[pos1].vazia = 0;
        T1[pos1].excluido = 0;
    } else {
        T2[pos2].num = T1[pos1].num;
        T2[pos2].vazia = 0;
        T1[pos1].num = n;
    }
}

void 
remover(int n, celula *T1, celula *T2)
{
    
}


void
imprimir


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
    }

    return EXIT_SUCCESS;
}