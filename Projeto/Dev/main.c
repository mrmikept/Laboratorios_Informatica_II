/**
 * @file main.c
 * @brief Ficheiro main.
 */
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "operators.h"
#include "parse.h"
#include "strings.h"
#include "blocos.h"

/**
 * @brief Função main.
 *
 * Primeiro cria uma nova stack com o auxilio da função new_Stack, lê uma linha dada pelo input e depois com o auxilio de um ciclo chama as funções getToken, MasterHandle, createString ou createBlock para a analise da linha recebida.
 * No final do processamento das diversas operações faz print dos elementos resultantes das operações na stack e faz free da memoria alocada para a mesma.
 *
 * @param Stack *s - Apontador para a Stack Criada.
 * @param char *line - String que guarda o conteúdo de uma linha.
 * @param char *token - String que guarda o conteudo de um token.
 * @param Function new_MainStack - Função que cria uma nova Stack.
 * @param Function createString(s, &line) - Função que cria uma string.
 * @param Function createBlock(s, &line) - Função que cria um bloco.
 * @param Function getToken(&line) - Função que faz parse dos tokens de uma linha
 * @param Function masterHandle(s, token) - Função Master Handle que chama as restantes funções handle.
 * @param Function printStack(s) - Função que faz print do conteudo da Stack.
 */
int main()
{
    STACK *s = new_MainStack();
    char *line = malloc(sizeof(char) * BUFSIZ);
    char *token;
    if (fgets(line, BUFSIZ, stdin) != NULL)
    {
        while (line[0] != '\0')
        {
            if (line[0] == ' ')
            {
                line++;
            }
            if (line[0] == '"')
            {
                createString(s, &line);
            }
            else if (line[0] == '{')
            {
                createBlock(s, &line);
            }
            else
            {
                token = getToken(&line);
                masterHandle(s, token, &line);
            }
        }
        printStack(s);
        free(s->stack);
        free(s->variables);
        free(s);
    }
    return 0;
}