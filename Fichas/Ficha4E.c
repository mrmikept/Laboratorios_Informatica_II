#include <stdio.h>
#include <string.h>
#define MAX 10000 //Tamanho maximo da sequencia.

int main()
{
	char str[MAX]; //Declaração da string.
	int maiorSeq = 1;
	int contaTamanho = 0;

	if (fgets(str, MAX, stdin) == NULL) //Se a linha for vazia(ou str[0] = '\0') retorna 0 na função.
	{
		return 0;
	}
	else
	{
		int tamanhoString = strlen(str); //tenho de declarar o tamanho da string numa variavel para não dar um warning.
		for (int i = 0; i < tamanhoString; i++)
		//Vamos percorer a array à procura de um caracter igual a stg[i]
		{
			for (int j = i + 1; j < tamanhoString; j++)
			//percorre o array em valores str[i+j] até encontrar um char igual.
			{
				if (str[i] == str[j])
				{
					contaTamanho = j - i + 1; 
				}
				for (int k = 1; k < contaTamanho / 2; k++)
				//Este ciclo esta aqui para verificar se os caracteres entre str[i] e str[j] são iguais para ser considerado uma sequencia refletida.
				{
					if (str[i + k] != str[j - k])
					//Se encontrar alguma diferença então define o tamanho entre str[i] e str[j] para 0 de modo a não alterar o valor da var maiorSeq
					{
						contaTamanho = 0;
						break;
					}
				}
				if (contaTamanho > maiorSeq)
				{
					maiorSeq = contaTamanho;
				}
			}
		}

		printf("%d\n", maiorSeq);

		return 0;
	}
}
