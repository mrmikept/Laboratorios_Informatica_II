#include <stdio.h>

int verificPrim();
int main() {
    int v1, v2, i; //v1 e v2 -> valor min e max para procurar primos // i -> valor usado para o ciclo for.
    printf("Insere dois numeros positivos:\n");
    if (scanf("%d %d",&v1,&v2) == 2) {
       if (v1 > v2) { //Troca de v1 por v2 se v1 > v2 (Ordenação.)
        v1 = v1 + v2;
        v2 = v1 - v2;
        v1 = v1 - v2;
       }
       printf("Os numeros primos entre %d e %d são:\n",v1,v2);
       int primo;
       for (i = v1 + 1; i < v2; i++) {
           primo = verificPrim(i);
           if (primo == 1)
           {
               printf("%d ", i);
           }
           
       } printf("\n");
       
    }
    return 0;
}

int verificPrim(int n) { //NUmeros primos são aqueles que somente são divisiveis por 1 e por ele mesmo. Então vamos usar um ciclo de for para verificar se existe
    int x, primo = 1;    //mais algum numero que possa dividir aquele numero, se houve então esta função retorna 0(False) se não houve então retorna 1(True)
    for (x = 2; x <= n/2; ++x) {
        if (n % x == 0) {
            primo = 0;
            break;
        }
    }
    return primo;
}