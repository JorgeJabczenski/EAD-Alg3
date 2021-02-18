#include "hash.h"

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

// seguindo a risca o algoritmo na especificao
// retornar int ou outra coisa?
int
busca(int n, celula *T1, celula *T2)
{
    int pos1 = h1(n,M);
    int pos2 = h2(n,M);
    if(T1[pos1].vazia == 1)
    {  
        // para consistencia, retornar -1? ou tratar como bool o retorno?
        return 0;
    } else if(T1[pos1].vazia == 0) {
        return pos1;
    } else {  // isso basta?
        return pos2;
    }
    
}


void 
inserir(int n, celula *T1, celula *T2)
{
    int pos1, pos2;

    pos1 = h1(n,M);
    pos2 = h2(n,M);  

    if (T1[pos1].vazia == 1 || (T1[pos1].excluido == 1))
    {
        T1[pos1].num = n;
        T1[pos1].vazia = 0;
        T1[pos1].excluido = 0;
    } else {
        T2[h2(T1[pos1].num, M)].num = T1[pos1].num;
        T2[h2(T1[pos1].num, M)].vazia = 0;
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
    if(T2[pos2].num == n){
        // acho que nao precisa marcar como excluida na tabela 2?
        // marcar com vazia?
        T2[pos2].vazia = 1;
    // entao checa a tabela 1
    } else if(T1[pos1].num == n){
        // conforme a especificao do trabalho
        T1[pos1].excluido = 1;
    // necessario checar se nao existe? na especificao da a entender que nao
    } else {
        fprintf(stderr, "Chave %d nao encontrada", n);
    }
}

// impressao simples das tabelas lado a lado
void
imprimir (celula *T1, celula *T2)
{
    int i, n1, n2;
    
    printf("\tT1\tT2\n");
    for(i = 0; i < M; i++){
        // -1 para significar NULL?
        if(T1[i].excluido || T1[i].vazia)
        {
            n1 = -1;
        } else {
            n1 = T1[i].num;
        }
        // entra o caso de nao saber o que marcar na exclusao de T2
        if(T2[i].vazia)
        {
            n2 = -1;
        } else {
            n2 = T2[i].num;
        }
        printf("%d\t%d\t%d\n", i,n1, n2);
    }
}