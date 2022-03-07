#include <stdio.h>

int verFactor(int n);
int main() {
    int a, b ,c;
    int menor, medio, maior = 0;
    if ((scanf("%d %d %d",&a,&b,&c)) != 3)
    {
        return 0;
    } else { //Primeiro temos de ordenar os tres valores de input para depois podermos usar a funcao verFactor(Verificar se é Factorial)
        if ((a > b) & (a > c)) {
            maior = a;
            if (b > c)
            {
                medio = b;
                menor = c;
            } else {
                medio = c;
                menor = b;
            }           
        }
        if ((b > a) & (b > c)) {
            maior = b;
            if (a > c)
            {
                medio = a;
                menor = c;
            } else {
                medio = c;
                menor = a;
            }
        }
        if ((c > a) & (c > b)) {
            maior = c;
            if (a > b) {
                medio = a;
                menor = b;
            } else {
                medio = b;
                menor = a;
            }
        }
        int t = verFactor(maior); //Vamos agora defenir um interno t que será o valor retornado pela funcao verFactor, se t = 1 entao o maior numero e fatorial, se t = 0 então não e fatorial, a variavel t funciona quase como um bool!
        if (t == 0) 
        {
            printf("%d %d %d\n", menor, medio, maior);
        } else {
            printf("FATORIAL\n");
        }
        
    }

    
    return 0;
}

int verFactor(int n) { //Vamos usar um ciclo for para verificar se a variavel n e um numero fatorial.
    int x=1;
    for (int i = 1; x<=n; i++){
        x = x * i;
        if ( x==n ){
            return 1;
        }
        else if (x > n){
            return 0;
        }
    }
    return 0;
}