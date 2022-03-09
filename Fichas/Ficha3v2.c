#include <stdio.h>

int verPrimo();
int verTriangular();
int main() {
    int v1=0, v2=0; //v1 e v2-> menor e maior valores do intervalo a procurar.
    if ((scanf("%d %d",&v1, &v2))==2) {
        int Primo=0,Triangular=0;
        Primo = verPrimo(v1, v2);
        Triangular = verTriangular(v1, v2);
        printf("%d %d\n",Triangular,Primo);
    }
    return 0;
}

//Numeros Primos são aqueles que são somentes divisiveis por 1 e por eles mesmos.
int verPrimo(int a,int b) {
    int prim = 0, x = 0;
    if (a==1) { //1 não é primo então fazemos um incremento ao a
        a++;
    }
    while (a <= b)
    {
        for(int i=2; i<=a/2; i++) {
            if (a % i == 0)
            {
                x = 1;
                break;
            } else x = 0;
        }
        if (x == 0) prim++;
        a++;
    }
    return prim;
}

//Numeros Triangulares são aqueles que podem ser representados na forma de triangulos equilateros.

int verTriangular(int c, int d) {
    int ft = 0, triang = 0;
    while (c <= d)
    {
        for(int j=0; j <= c; j++) {
            if ((((j+1)*j)/2) == c) {
                ft = 1;
                break;
            } else ft = 0;
        }
        if (ft == 1) triang++;
        c++;
    }
    return triang;
}