/**
 * @file parse.c
 * @brief Ficheiro parse.c que contém todas as funções relativas a operações de conversão e identificação de tipos.
 */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "stack.h"

// void *createRef(STACK_ELEM x)
// {
//     void *pt;
//     if (x.t == INT)
//     {
//         void *pt = malloc(sizeof(long));
//         *(long *) pt = *(long *) x.elem;
//     }
//     if (x.t == DBL)
//     {
//         void *pt = malloc(sizeof(double));
//         *(double *) pt = *(double *) x.elem;
//     }
//     if (x.t == CHAR)
//     {
//         void *pt = malloc(sizeof(char));
//         *(char *) pt = *(char *)x.elem;
//     }
//     if (x.t == ARR)
//     {
//         void *pt = malloc(sizeof(STACK));
//         *(STACK *) pt = *(STACK*) x.elem;
//     }
//     // if (x.t == STR)
//     // {
//     //     int strsize = strlen(x.elem) + 1;
//     //     void *pt = malloc(sizeof(char) * strsize);
//     //     pt = x.elem;
//     // }
//     return pt;
// }

/**
 * @brief Função que separa a string line em token pelos espaços.
 * 
 * Com o auxílio de um ciclo for é criada uma string result com o tamanho do token, é verificado se no incio da linha existem espaços, se sim é incrementado a string line, depois é percorrido a string line e guardado o seu valor em result até ser encontrado o caracter ' ', '\n' ou '\0'.
 * No fim devolve a string result para ser atribuida ao um token.
 * @param[in] char **line - Apontador para uma string line. 
 * @return result - Retorna uma string com o token 
 */
char *getToken(char **line)
{
    char *token = malloc(sizeof(char) * BUFSIZ);
    int i = 0, s = 0;
    while (*line[0] == ' ')
    {
        (*line)++;
    }
    if (*line[0] == '\0')
    {
        token = '\0';
        return token;
    }
    
    for (i = 0; *line[0] != ' ' && *line[0] != '\0' && *line[0] != '\n'; i++)
    {
        s++;
        token[i] = *line[0];
        (*line)++;
    }
    (*line)++;
    token[s] = '\0';
    char *result = malloc(sizeof(char) * s);
    strcpy(result, token);
    free(token);
    return result;
}

// Função que verifica se o tipo da string token é INT ou DOUBLE
/**
 * @brief Função que verifica se o tipo da string token é do tipo Inteiro ou Double.
 *
 * Com o auxilio de um ciclo for, verifica se os elementos da string são caracteres numericos e se possuem o char ' . ' , mudando o valor da variável flag para o respetivo enum do tipo. No fim retorna o valor da flag à função tkType.
 * @param[in] token - Recebe um token.
 * @return int flag.
 */
int tokenTypeID(char *token)
{
    int flag = -1; // 0 = CHAR, 1 = INT, 2 = DBL, 3 = STR.
    for (int i = 0; token[i] && token[i] != '\0'; i++)
    {
        if (token[i] < '0' || token[i] > '9') // string double(ponto)
        {
            if (flag == INT && token[i] == '.' && token[i + 1])
            {
                flag = DBL;
            }
        }
        else if (flag == -1)
        {
            flag = INT;
        }
    }
    return flag;
}

// Função que verifica o tipo da string token
/**
 * @brief Função que verifica o tipo da string token.
 *
 * Primeiro com o tokenLenght recebido pela função val verifica o seu tamanho, se for igual a 1 então é um inteiro, se for maior chama a função tokenTypeIDS, retornando o enum do tipo.
 * @param[in] token - Recebe um token.
 * @param[in] tokenLength - Recebe o tamanho da string token.
 * @return int - Retorna o enum do tipo detectado.
 * @param Function tokenTypeIDS(token) - Verifica se a string token é um Int, um Double ou uma string.
 */
int tokenType(char *token, int tokenLength)
{
    if (tokenLength == 1)
    {
        return INT;
    }
    else
    {
        return tokenTypeID(token);
    }
}

/**
 * @brief Converte o elemento no topo da stack para um inteiro.
 *
 * É comparado o token com o character ' i ':
 * - Se for igual então verifica de que tipo é o elemento no topo da stack de forma a poder fazer type cast correto para inteiro. No fim faz push da variavel stackTOP com a conversão para inteiro do elemento e retorna 1 À função parseHandle.
 * - Se não for igual retorna 0 à função parseHandle.
 * @param[in] s - Recebe um apontador para a stack.
 * @param[in] token - Recebe um token.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param void *intPt - Apontador void com o tamanho de um long.
 * @param STACK_ELEM stackTOP - Com o auxilio da função pop guarda o elemento que está no topo da stack.
 * @param Function push(s, stackTOP) - Coloca no topo da stack o valor da conversão.
 */
int convertInt(STACK *s, char *token)
{
    if (strcmp(token, "i") == 0)
    {
        STACK_ELEM stackTOP = pop(s);
        void *intPt = malloc(sizeof(long)); // criar apontador void para uma nova referencia com o tamanho para um long
        if (stackTOP.t == STR)
        {
            sscanf(stackTOP.elem, "%ld", (long *)intPt); // parse de uma string para inteiro
        }
        else if (stackTOP.t == DBL)
        {
            *(long *)intPt = *(double *)stackTOP.elem;
        }
        else if (stackTOP.t == CHAR)
        {
            long teste = (long) (*(char*)stackTOP.elem);
            *(long *)intPt = teste;
        }
        else
        {
            *(long *)intPt = *(long *)stackTOP.elem;
        }
        stackTOP.elem = intPt;
        stackTOP.t = INT;
        push(s, stackTOP);
        return 1;
    }
    return 0;
}

/**
 * @brief Converte o elemento no topo da stack para um carácter.
 *
 * É comparado o token com o character ' c ':
 * - Se for igual então verifica de que tipo é o elemento no topo da stack de forma a poder fazer type cast correto para um carácter. No fim faz push da variavel stackTOP com a conversão para carácter do elemento e retorna 1 À função parseHandle.
 * - Se não for igual retorna 0 à função parseHandle.
 * @param[in] s - Recebe um apontador para a stack.
 * @param[in] token - Recebe um token.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param STACK_ELEM stackTOP - Com o auxilio da função pop guarda o elemento que está no topo da stack.
 * @param void *intPt - Apontador void para um inteiro.
 * @param void *charPt - Apontador void com o tamanho de um carácter.
 * @param Function push(s, stackTOP) - Coloca no topo da stack o valor da conversão.
 */
int convertChar(STACK *s, char *token)
{
    if (strcmp(token, "c") == 0)
    {
        STACK_ELEM stackTOP = pop(s);
        void *intPt;
        if (stackTOP.t == INT)
        {
            intPt = stackTOP.elem;
        }
        else
        {
            intPt = malloc(sizeof(long));
            sscanf(stackTOP.elem, "%ld", (long *)intPt);
        }
        void *charPt = malloc(sizeof(char));
        *(char *)charPt = (char)(*(long *)intPt);
        stackTOP.elem = charPt;
        stackTOP.t = CHAR;
        push(s, stackTOP);
        return 1;
    }
    return 0;
}

/**
 * @brief Converte o elemento no topo da stack para um double.
 *
 * É comparado o token com o caracter ' f ':
 * - Se for igual então verifica de que tipo é o elemento no topo da stack de forma a poder fazer type cast correto para um double. No fim faz push da variavel stackTOP com a conversão para carácter do elemento e retorna 1 À função parseHandle.
 * - Se não for igual retorna 0 à função parseHandle.
 * @param[in] s - Recebe um apontador para a stack.
 * @param[in] token - Recebe um token.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param STACK_ELEM stackTOP - Com o auxilio da função pop guarda o elemento que está no topo da stack.
 * @param void *doublePt - Apontador void com o tamanho de um double.
 * @param Function push(s, stackTOP) - Coloca no topo da stack o valor da conversão.
 */
int convertDbl(STACK *s, char *token)
{
    if (strcmp(token, "f") == 0)
    {
        STACK_ELEM stackTOP = pop(s);
        char *str = stackTOP.elem;
        void *doublePt = malloc(sizeof(double));
        if (stackTOP.t == STR)
        {
            *(double *)doublePt = strtod(str, NULL);
        }
        else if (stackTOP.t == INT)
        {
            *(double *)doublePt = *(long *)stackTOP.elem;
        }
        else
        {
            *(double *)doublePt = *(double *)stackTOP.elem;
        }
        stackTOP.t = DBL;
        stackTOP.elem = doublePt;
        push(s, stackTOP);
        return 1;
    }
    return 0;
}

/**
 * @brief Converte o elemento no topo da stack para um double.
 *
 * É comparado o token com o caracter ' s ':
 * - Se for igual então verifica de que tipo é o elemento no topo da stack de forma a poder fazer type cast correto para uma string. No fim faz push da variavel stackTOP com a conversão para carácter do elemento e retorna 1 À função parseHandle.
 * - Se não for igual retorna 0 à função parseHandle.
 * @param[in] s - Recebe um apontador para a stack.
 * @param[in] token - Recebe um token.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param STACK_ELEM stackTOP - Com o auxilio da função pop guarda o elemento que está no topo da stack.
 * @param char *str - Declaração de uma string com o tamanho necessario para criar a string.
 * @param Function push(s, stackTOP) - Coloca no topo da stack o valor da conversão.
 */
int convertString(STACK *s, char *token)
{
    if (strcmp(token, "s") == 0)
    {
        STACK_ELEM stackTOP = pop(s);
        if (stackTOP.t == INT)
        {
            char *str = malloc((ceil(log10(*(long *)stackTOP.elem)) + 1) * sizeof(char));
            sprintf(str, "%d", (*(int *)stackTOP.elem));
            stackTOP.t = STR;
            stackTOP.elem = str;
            push(s, stackTOP);
            return 1;
        }
        else if (stackTOP.t == DBL)
        {
            char *str = malloc((ceil(log10(*(double *)stackTOP.elem)) + 1) * sizeof(char));
            sprintf(str, "%g", (*(double *)stackTOP.elem));
            stackTOP.t = STR;
            stackTOP.elem = str;
            push(s, stackTOP);
            return 1;
        }
        else if (stackTOP.t == CHAR)
        {
            char *str = malloc(sizeof(char) + 1);
            sprintf(str, "%c", (*(char *)stackTOP.elem));
            stackTOP.t = STR;
            stackTOP.elem = str;
            push(s, stackTOP);
        }
    }
    return 0;
}

/**
 * @brief Função PARSE Handle que chama as funções de operações de conversão.
 *
 * @param[in] s Recebe um apontador para a stack.
 * @param[in] token Recebe um token.
 * @retval 1 se foi executada com êxito.
 * @retval 0 se não foi executada com êxito.
 * @param Function convertInt(s, token) - Função que converte o topo da stack num inteiro.
 * @param Function convertDbl(s, token) - Função que converte o topo da stack num double.
 * @param Function convertChar(s, token) - Função que converte o topo da stack num carácter.
 * @param Function convertString(s, token) - Função que converte o topo da stack numa string.
 */
int parseHandle(STACK *s, char *token)
{
    return (convertInt(s, token) || convertDbl(s, token) || convertChar(s, token) || convertString(s, token));
}