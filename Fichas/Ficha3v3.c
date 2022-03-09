#include <stdio.h>

int main() {
    int v1, v2,primo=0,triangular=0,fp=0,ft=0;
    if ((scanf("%d %d",&v1, &v2))==2)
    {
        while (v1 <= v2)
        {
            if (v1 > 1) { //Numero primo é aquele que é somente divisivel por 1 e por ele mesmo. 1 não é numero primo logo se v1 <= 1 ele não inicia o ciclo de for que calcula os primos.
            for(int i=2; i<=v1/2; i++) { //Ciclo para Primo que testa se algum numero desdo 2 até a v1/2 é divisivel por v1.
                if (v1 % i == 0 || v1 % 2 == 0) //Se esta condição for verdadeira então fp muda para 1(False), caso contrario muda para 0(True)
                {
                    fp = 1; //fp = 1 (False, Não é primo) //fp = 0 (True, é numero primo.)
                    break;
                } else fp = 0;
                }
            if (fp == 0) primo++; //No fim do ciclo se fp for igual a 0 então incrementa a variavel que guarda o numero de primos.
            }
            int sum=0; //Numeros triangulares são aqueles que formam um triangulo equilatero.
            for(int j=1; sum <= v1; j++) { //Ciclo para Triangular
                sum = sum + j; //Um numero é triangular se a soma de numeros consecutivos por igual a esse numero.
                if (sum == v1) { //Se a variavel sum for igual a v1 então v1 é numero triangular.
                    ft = 1; //ft = 1 (True, é triangular) //ft = 0 (False, não é triangular)
                    break;
                } else ft = 0;
            }
        if (ft == 1) triangular++; //No fim do ciclo se ft == 1 então incrementa a variavel que guarda o numero de triangulares
        v1++; //incremento ao v1 para o ciclo while
        }
    }
    printf("%d %d\n",triangular,primo);
    return 0;
}
