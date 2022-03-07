#include <stdio.h>

int verificTriang();
int verificPrim();
int main() {
    int v1, v2, i; //v1 e v2 -> valor min e max para procurar primos e numeros triangulares // i -> valor usado para o ciclo for.
    if (scanf("%d %d",&v1,&v2) == 2) {
       if (v1 > v2) { //Troca de v1 por v2 se v1 > v2 (Ordenação.)
        v1 = v1 + v2;
        v2 = v1 - v2;
        v1 = v1 - v2;
       }
       int primo, triang;
       int p = 0, t = 0;
       for (i = v1 + 1; i < v2; i++) { //ciclo for que conta a quantidade de numeros primos e triangulares entre v1 e v2
           triang = verificTriang(i);
           primo = verificPrim(i);
           if (primo == 1)
           {
               p++;
           }
           if (triang == 1) {
               t++;
           }
         
       }  printf("%d %d\n", t, p);
       
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

int verificTriang(int n) {
    int z, tg, triangular = 0;
    for (z = 1; z <= 2 ^ 25; z++) {
        tg = ((z * (z + 1))/2);
        if (tg == n)
        {
            triangular = 1;
            break;
        }
        
    }
    return triangular;
}