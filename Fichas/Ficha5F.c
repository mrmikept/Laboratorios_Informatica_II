/* [Problema F]

DESCRIÇÃO:
    
    -Uma empresa regista num ficheiro texto as compras que os seus clientes fazem. Cada linha corresponde aos produtos comprados por um cliente.
    -Os produtos estão codificados por uma única letra entre ‘A’ e ‘Z’. Pretende-se imprimir a contagem de produtos que saíram de stock bem como a contagem da compra conjunta de cada dois produtos.
    -Para a lista impressa não ser muito longa há um parâmetro que indica a frequência mínima que cada produto ou pares de produtos deve ter para a sua contagem aparecer na listagem.

INPUT:

    -A primeira linha de texto contém o valor mínimo de frequência F.
    -As restantes linhas contém a designação dos produtos de cada compra de um cliente, sendo separados por espaços.
    -Cada produto aparece uma única vez.

OUTPUT:

    -O seu programa deve imprimir, por ordem alfabética os produtos, ou pares de produtos, seguidos de um igual e da respetiva contagem. 
    -Só serão impressas linhas em que a contagem seja maior ou igual a F.

SAMPLE TESTS:

Input 1
1
A B C
F A D
B A F

Output 1
A = 3
AB = 2
AC = 1
AD = 1
AF = 2
B = 2
BC = 1
BF = 1
C = 1
D = 1
DF = 1
F = 2
*/

#include <stdio.h>
#include <string.h>

#define MAX 52

int main()
{
    int F = 0;
    char input[52];
    int vendas[26][26];
    // Vamos inicializar o array2D todo a 0.
    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            vendas[i][j] = 0;
        }
    }

    // Usando o scanf vamos receber o valor de frequencia minima F
    if ((scanf("%d", &F) == 1))
    {
        // Vamos usar o fgets para receber a linha com os artigos vendidos e, ignorando os \n, \n e ' ' vamos colocar os artigos vendidos numa array2D onde as linhas e colunas representam os artigos(A..Z)
        // sabendo o código ASCII dos caracteres(A = 65, B = 66, ..., Z = 90) subtraindo 65 sabemos em que coluna e linha somar 1.
        while ((fgets(input, 52, stdin)) != NULL)
        {
            int tamanho = strlen(input);
            for (int i = 0; i < tamanho; i++)
            {
                if (input[i] != '\0' && input[i] != ' ' && input[i] != '\n')
                {
                    int x = input[i];
                    for (int j = 0; j < tamanho; j++)
                    {
                        if (input[j] != '\0' && input[j] != ' ' && input[j] != '\n')
                        {
                            int y = input[j];
                            vendas[x - 65][y - 65] += 1;
                        }
                    }
                }
            }
        }

        // Para os pares de produtos aparecerem por ordem no output só precisamos de imprimir o triangulo superior da matriz, então defenimos um limite l.
        int limite = 1;
        for (int i = 0; i < 26; i++)
        {
            if (vendas[i][i] >= F)
            {
                // temos de somar novamente 65 para termos o valor ASCII do caracter para o poder imprimir, vamos guardar esses valores nas variaveis car1(caracter 1) e car2(caracter 2)
                int car1 = i + 65;
                printf("%c = %d\n", car1, vendas[i][i]);
            }
            for (int j = limite; j < 26; j++)
            {
                if (vendas[i][j] >= F)
                {
                    int car1 = i + 65;
                    int car2 = j + 65;
                    printf("%c%c = %d\n", car1, car2, vendas[i][j]);
                }
            }
            limite++;
        }
    }
    return 0;
}

