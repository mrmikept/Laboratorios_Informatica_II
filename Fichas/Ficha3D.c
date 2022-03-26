#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{
    int i, j, v1, v2, primo = 0, triangular = 0;
    if ((scanf("%d %d", &v1, &v2)) == 2)
    {
        bool *primes = malloc(sizeof(bool) * (v2 + 1)); // Alocar um array com o tamanho maximo fornecido (v2).

        for (i = 2; i <= v2; i++) // Inicializar o array a true
            primes[i] = true;

        i = 2;
        while ((i * i) <= v2) // Criação do crivo de eratostenes
        {
            if (primes[i] != false)
            {
                for (j = 2; j < v2; j++)
                {
                    if ((primes[i] ? i : 0) * j > v2)
                        break;
                    else
                        primes[(primes[i] ? i : 0) * j] = false;
                }
            }
            i++;
        }

        while (v1 <= v2)
        {
            // Conta todos os numeros primos usando o crivo. Ou seja, incrementa se a posição no array estiver a false.
            if (primes[v1] != false)
            {
                primo++;
            }
            // Conta todos os numeros triangulares.
            int a = sqrt(2 * v1 + 0.25) - 0.5;
            int b = a;
            if (b == a && ((b * (b + 1)) / 2) == v1)
                triangular++;

            v1++;
        }
        free(primes);
    }
    printf("%d %d\n", triangular, primo);
    return 0;
}