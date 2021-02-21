/* GRR20190372 & GRR20190367 */
/* jlvj19      &      vtvd19 */

#include "hash.h"

void 
inicializaVetor(celula* v, int t)
{
    for (int i = 0; i < t; i++)
    {
        v[i].excluido = 0;
        v[i].vazio    = 1;
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

int
busca(int n, celula *T1, celula *T2)
{
    int pos1 = h1(n,M);
    int pos2 = h2(n,M);

    if (T1[pos1].num == n && !T1[pos1].excluido){
        return pos1;
    } else if (T2[pos2].num == n && !T2[pos2].vazio){  
        return pos2;
    }

    return -1; // Posição inválida
    
}

void 
inserir(int n, celula *T1, celula *T2)
{
    int pos1;

    pos1 = h1(n,M);

    /* Como não pode haver chaves repetidas */
    if (T1[pos1].num != n)
    {
        if (T1[pos1].vazio == 1 || (T1[pos1].excluido == 1))
        {
            T1[pos1].vazio    = 0;
            T1[pos1].excluido = 0;
        } else {
            int novaPos = h2(T1[pos1].num, M);

            T2[novaPos].num   = T1[pos1].num;
            T2[novaPos].vazio = 0;
        }
        T1[pos1].num = n;
    }
}

void 
remover(int n, celula *T1, celula *T2)
{
    int pos1, pos2;

    pos1 = h1(n,M);
    pos2 = h2(n,M);

    // trata tabela 2 antes
    if(T2[pos2].num == n && !T2[pos2].vazio){
        T2[pos2].vazio = 1;
    // entao checa a tabela 1
    } else if(T1[pos1].num == n){
        // conforme a especificao do trabalho
        T1[pos1].excluido = 1;
    } 
}

void
imprimir (celula *T1, celula *T2)
{
    int cont;
    /* As duas tabelas podem estar completas, por isso o 2M */
    int impressao[2*M][3];

    cont = 0;

    for (int i = 0; i < M; i++)
    {
        impressao[i][0] = 0; // Número
        impressao[i][1] = 0; // Tabela (1 ou 2)
        impressao[i][2] = 0; // Posição
    }

    /* Obtém todos os valores em todas as tabelas, guardando seyu valor, tabela e posição */
    for (int i = 0; i < M; i++)
    {
        if (!T1[i].vazio && !T1[i].excluido)
        {
            impressao[cont]  [0] = T1[i].num;
            impressao[cont]  [1] = 1;
            impressao[cont++][2] = i;
        }
        if (!T2[i].vazio)
        {
            impressao[cont]  [0] = T2[i].num;
            impressao[cont]  [1] = 2;
            impressao[cont++][2] = i;
        }
    }

    /* Ordena por Insertion Sort, usando o primeiro valor como parâmetro */
    for (int i = 1; i < cont; i++)
    {
        int key[3];
        
        key[0] = impressao[i][0];
        key[1] = impressao[i][1];
        key[2] = impressao[i][2];
        
        int j = i - 1;

        while ((j >= 0) && (impressao[j][0] > key[0]))
        {
            impressao[j+1][0] = impressao[j][0];
            impressao[j+1][1] = impressao[j][1];
            impressao[j+1][2] = impressao[j][2];

            j--;
        }

        impressao[j+1][0] = key[0];
        impressao[j+1][1] = key[1];
        impressao[j+1][2] = key[2];
    }


    /* Imprime a tabela final ordenada */
    for (int i = 0; i < cont; i++)
    {
        printf("%d,T%d,%d\n", impressao[i][0], impressao[i][1], impressao[i][2]);
    }
}