#include <stdio.h>


int verPrimo();
int verTriang();
int main() {
    int v1, v2, i; //v1 e v2 -> valor min e max para procurar primos e numeros triangulares // i -> valor usado para o ciclo for.
    if (scanf("%d %d",&v1,&v2) == 2) {
       if (v1 > v2) { //Troca de v1 por v2 se v1 > v2 (Ordenação.)
        int c = v1;
        v1 = v2;
        v2 = c;
       }
       int np=0, nt=0, primo=0, triang=0;
       primo = verPrimo(v1, v2);
       triang = verTriang(v1, v2);
    printf("%d %d\n",triang, primo);
    }
    return 0;
}

int verPrimo(int n) { //NUmeros primos são aqueles que somente são divisiveis por 1 e por ele mesmo. Então vamos usar um ciclo de for para verificar se existe
    int x, primo = 1;    //mais algum numero que possa dividir aquele numero, se houve então esta função retorna 0(False) se não houve então retorna 1(True)
    for (x = 2; x <= n/2; ++x) {
        if (n % x == 0) {
            primo = 0;
            break;
        }
    }
    return primo;
}

int verTriang(int n,int b) {
    for (int j = 0; j <= n; j++)
    {
        if ((((j+1)*j)/2) == n)
        {
            return 1;
            break;
        }
        
    }
    return 0;
}
