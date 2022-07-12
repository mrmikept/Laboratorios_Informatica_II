/**
 * @file Logica.c
 * @brief Ficheiro Logica.c que contém todas as funções relativas a operações condicionais.
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stack.h"

/**
 * @brief Função de operação e&(Condicional).
 *
 * É comparado o token com a string " e& ":
 * - Se for igual então guarda os dois valores do topo da stack nas variaveis x e y, é verificado se x possui valor de verdade(diferente de 0), se possuir é feito o push de y para a stack, caso contrario é inserido 0 na stack, e no final devolve 1 à função conditionalHandle.
 * - Se for diferente devolve 0 à função conditionalHandle.
 * @param[in] s - Recebe um apontador para a stack.
 * @param[in] token - Recebe um token.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param STACK_ELEM x - Guarda o segundo valor do topo da stack com o auxilio da função pop.
 * @param STACK_ELEM y - Guarda o primeiro valor do topo da stack com o auxilio da função pop.
 * @param STACK_ELEM condValue - Variavel para guardar o elemento 0 caso x e/ou y sejam falsos.
 * @param void *IntPt - Apontador void com o tamanho de um long.
 * @param Function pop(s) - Remove um elemento da stack.
 * @param Function push(s, <elemento>) - Faz push para a stack do resultado da condição, y se x for verdadeiro e 0 se x for falso.
 */
int eCond(STACK *s, char *token)
{
    if (strcmp(token, "e&") == 0)
    {
        STACK_ELEM y = pop(s);
        STACK_ELEM x = pop(s);
        if ((x.t == INT && *(long *)x.elem != 0) || (x.t == DBL && *(double *)x.elem != 0) || (x.t == CHAR && *(char *)x.elem != 0))
        {
            push(s, y);
            free(x.elem);
            return 1;
        }
        else
        {
            STACK_ELEM condValue;
            void *intPt = malloc(sizeof(long));
            *(long *)intPt = 0;
            condValue.t = INT;
            condValue.elem = intPt;
            push(s, condValue);
            free(x.elem);
            free(y.elem);
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Função de operação e|(Condicional).
 *
 * É comparado o token com a string " e| ":
 * - Se for igual então guarda os dois valores do topo da stack nas variaveis x e y, é verificado se x possui valor de falso(igual a 0), se possuir é feito o push de y para a stack, caso contrario é feito push de x para a stack, e no final devolve 1 à função conditionalHandle.
 * - Se for diferente devolve 0 à função conditionalHandle.
 * @param[in] s - Recebe um apontador para a stack.
 * @param[in] token - Recebe um token.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param STACK_ELEM x - Guarda o segundo valor do topo da stack com o auxilio da função pop.
 * @param STACK_ELEM y - Guarda o primeiro valor do topo da stack com o auxilio da função pop.
 * @param Function pop(s) - Remove um elemento da stack.
 * @param Function push(s, <elemento>) - Faz push para a stack do resultado da condição, y se x for falso e x se for verdadeiro.
 */
int ouCond(STACK *s, char *token)
{
    if (strcmp(token, "e|") == 0)
    {
        STACK_ELEM y = pop(s);
        STACK_ELEM x = pop(s);
        if ((x.t == INT && *(long *)x.elem == 0) || (x.t == DBL && *(double *)x.elem == 0) || (x.t == CHAR && *(char *)x.elem == 0))
        {
            push(s, y);
            free(x.elem);
            return 1;
        }
        else
        {
            push(s, x);
            free(y.elem);
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Função auxiliar da função menorCond(Função caso x seja um inteiro).
 *
 * Utilizamos uma condição para saber qual é o tipo de y e fazemos push do menor para a stack.
 * @param[in] s - Recebe um apontador para a stack.
 * @param[in] x - Recebe o segundo elemento da stack.
 * @param[in] y - Recebe o primeiro elemento da stack.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param Function push(s, x) - Coloca no topo da stack o elemento x.
 * @param Function push(s, y) - Coloca no topo da stack o elemento y.
 */
int menorCondInt(STACK *s, STACK_ELEM x, STACK_ELEM y)
{
    if (y.t == INT && *(long *)x.elem < *(long *)y.elem)
    {
        push(s, x);
        free(y.elem);
        return 1;
    }
    else if (y.t == DBL && *(long *)x.elem < *(double *)y.elem)
    {
        push(s, x);
        free(y.elem);
        return 1;
    }
    else if (y.t == CHAR && *(long *)x.elem < *(char *)y.elem)
    {
        push(s, x);
        free(y.elem);
        return 1;
    }
    else
    {
        push(s, y);
        free(x.elem);
        return 1;
    }
    return 0;
}

/**
 * @brief Função auxiliar da função menorCond(Função caso x seja um double).
 *
 * Utilizamos uma condição para saber qual é o tipo de y e fazemos push do menor para a stack.
 * @param[in] s - Recebe um apontador para a stack.
 * @param[in] x - Recebe o segundo elemento da stack.
 * @param[in] y - Recebe o primeiro elemento da stack.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param Function push(s, x) - Coloca no topo da stack o elemento x.
 * @param Function push(s, y) - Coloca no topo da stack o elemento y.
 */
int menorCondDbl(STACK *s, STACK_ELEM x, STACK_ELEM y)
{
    if (y.t == INT && *(double *)x.elem < *(long *)y.elem)
    {
        push(s, x);
        free(y.elem);
        return 1;
    }
    else if (y.t == DBL && *(double *)x.elem < *(double *)y.elem)
    {
        push(s, x);
        free(y.elem);
        return 1;
    }
    else if (y.t == CHAR && *(double *)x.elem < *(char *)y.elem)
    {
        push(s, x);
        free(y.elem);
        return 1;
    }
    else
    {
        push(s, y);
        free(x.elem);
        return 1;
    }
    return 0;
}

/**
 * @brief Função auxiliar da função menorCond(Função caso x seja uma string).
 *
 * Utilizamos uma condição para saber qual é a string de menor dimensão e fazemos push da menor para a stack e libertando a mémoria da outra string.
 * @param[in] s - Recebe um apontador para a stack.
 * @param[in] x - Recebe o segundo elemento da stack.
 * @param[in] y - Recebe o primeiro elemento da stack.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param Function push(s, x) - Coloca no topo da stack o elemento x.
 * @param Function push(s, y) - Coloca no topo da stack o elemento y.
 */
int menorCondString(STACK *s, STACK_ELEM x, STACK_ELEM y)
{
    if (strcmp(x.elem, y.elem) < 0)
    {
        push(s, x);
        free(y.elem);
        return 1;
    }
    else
    {
        push(s, y);
        free(x.elem);
        return 1;
    }
    return 0;
}

/**
 * @brief Função auxiliar da função menorCond(Função caso x seja um char).
 *
 * Utilizamos uma condição para saber qual é o tipo de y e fazemos push do menor para a stack.
 * @param[in] s - Recebe um apontador para a stack.
 * @param[in] x - Recebe o segundo elemento da stack.
 * @param[in] y - Recebe o primeiro elemento da stack.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param Function push(s, x) - Coloca no topo da stack o elemento x.
 * @param Function push(s, y) - Coloca no topo da stack o elemento y.
 */
int menorCondChar(STACK *s, STACK_ELEM x, STACK_ELEM y)
{
    if (y.t == INT && *(char *)x.elem < *(long *)y.elem)
    {
        push(s, x);
        free(y.elem);
        return 1;
    }
    else if (y.t == DBL && *(char *)x.elem < *(double *)y.elem)
    {
        push(s, x);
        free(y.elem);
        return 1;
    }
    else if (y.t == CHAR && *(char *)x.elem < *(char *)y.elem)
    {
        push(s, x);
        free(y.elem);
        return 1;
    }
    else
    {
        push(s, y);
        free(x.elem);
        return 1;
    }
    return 0;
}

/**
 * @brief Função de operação menor de dois valores do topo da stack.
 *
 *  É comparado o token com o caracter ' e< ',
 *  - Se for igual então guarda os dois valores no topo da stack nas variaveis x e y, com o auxilio de uma condição verifica o tipo de x e usa uma função auxiliar para determinar qual o menor elemento.
 *  - Retorna 1 se a operação foi executada com sucesso, caso contrario retorna 0.
 * @param[in] s Recebe um apontador para a stack.
 * @param[in] token Recebe um token.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param STACK_ELEM x - Guarda o primeiro valor do topo da stack com o auxilio da função pop.
 * @param STACK_ELEM y - Guarda o segundo valor do topo da stack com o auxilio da função pop.
 * @param Function menorCondInt(s, x, y) - Função auxiliar da função menorCond(Função caso x seja um inteiro).
 * @param Function menorCondDbl(s, x, y) - Função auxiliar da função menorCond(Função caso x seja um double).
 * @param Function menorCondChar(s, x, y) - Função auxiliar da função menorCond(Função caso x seja um caractere).
 * @param Function menorCondString(s, x, y) - Função auxiliar da função menorCond(Função caso x seja uma string).
 */
int menorCond(STACK *s, char *token)
{
    if (strcmp(token, "e<") == 0)
    {
        STACK_ELEM y = pop(s);
        STACK_ELEM x = pop(s);
        if (x.t == INT)
        {
            return menorCondInt(s, x, y);
        }
        else if (x.t == DBL)
        {
            return menorCondDbl(s, x, y);
        }
        else if (x.t == CHAR)
        {
            return menorCondChar(s, x, y);
        }
        else
        {
            menorCondString(s, x, y);
        }
    }
    return 0;
}

/**
 * @brief Função auxiliar da função maiorCond(Função caso x seja um inteiro).
 *
 * Utilizamos uma condição para saber qual é o tipo de y e fazemos push do maior para a stack.
 * @param[in] s - Recebe um apontador para a stack.
 * @param[in] x - Recebe o segundo elemento da stack.
 * @param[in] y - Recebe o primeiro elemento da stack.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param Function push(s, x) - Coloca no topo da stack o elemento x.
 * @param Function push(s, y) - Coloca no topo da stack o elemento y.
 */
int maiorCondInt(STACK *s, STACK_ELEM x, STACK_ELEM y)
{
    if (y.t == INT && *(long *)x.elem > *(long *)y.elem)
    {
        push(s, x);
        free(y.elem);
        return 1;
    }
    else if (y.t == DBL && *(long *)x.elem > *(double *)y.elem)
    {
        push(s, x);
        free(y.elem);
        return 1;
    }
    else if (y.t == CHAR && *(long *)x.elem > *(char *)y.elem)
    {
        push(s, x);
        free(y.elem);
        return 1;
    }
    else
    {
        push(s, y);
        free(x.elem);
        return 1;
    }
    return 0;
}

/**
 * @brief Compara os elemento do topo da stack e devolve o maior(função para o caso de x ser um double).
 *
 * Utilizamos uma condição para saber qual é o tipo de y e fazemos push do maior para a stack.
 * @param[in] s - Recebe um apontador para a stack.
 * @param[in] x - Recebe o segundo elemento da stack.
 * @param[in] y - Recebe o primeiro elemento da stack.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param Function push(s, x) - Coloca no topo da stack o elemento x.
 * @param Function push(s, y) - Coloca no topo da stack o elemento y.
 */
int maiorCondDbl(STACK *s, STACK_ELEM x, STACK_ELEM y)
{
    if (y.t == INT && *(double *)x.elem > *(long *)y.elem)
    {
        push(s, x);
        free(y.elem);
        return 1;
    }
    else if (y.t == DBL && *(double *)x.elem > *(double *)y.elem)
    {
        push(s, x);
        free(y.elem);
        return 1;
    }
    else if (y.t == CHAR && *(double *)x.elem > *(char *)y.elem)
    {
        push(s, x);
        free(y.elem);
        return 1;
    }
    else
    {
        push(s, y);
        free(x.elem);
        return 1;
    }
    return 0;
}

/**
 * @brief Compara os elemento do topo da stack e devolve o maior(função para o caso de x ser um char).
 *
 * Utilizamos uma condição para saber qual é o tipo de y e fazemos push do maior para a stack.
 * @param[in] s - Recebe um apontador para a stack.
 * @param[in] x - Recebe o segundo elemento da stack.
 * @param[in] y - Recebe o primeiro elemento da stack.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param Function push(s, x) - Coloca no topo da stack o elemento x.
 * @param Function push(s, y) - Coloca no topo da stack o elemento y.
 */
int maiorCondChar(STACK *s, STACK_ELEM x, STACK_ELEM y)
{
    if (y.t == INT && *(char *)x.elem > *(long *)y.elem)
    {
        push(s, x);
        free(y.elem);
        return 1;
    }
    else if (y.t == DBL && *(char *)x.elem > *(double *)y.elem)
    {
        push(s, x);
        free(y.elem);
        return 1;
    }
    else if (y.t == CHAR && *(char *)x.elem > *(char *)y.elem)
    {
        push(s, x);
        free(y.elem);
        return 1;
    }
    else
    {
        push(s, y);
        free(x.elem);
        return 1;
    }
    return 0;
}

/**
 * @brief Função auxiliar da função maiorCond(Função caso x seja uma string).
 *
 * Utilizamos uma condição para saber qual é a string de maior dimensão e fazemos push da maior para a stack e libertando a mémoria da outra string.
 * @param[in] s - Recebe um apontador para a stack.
 * @param[in] x - Recebe o segundo elemento da stack.
 * @param[in] y - Recebe o primeiro elemento da stack.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param Function push(s, x) - Coloca no topo da stack o elemento x.
 * @param Function push(s, y) - Coloca no topo da stack o elemento y.
 */
int maiorCondString(STACK *s, STACK_ELEM x, STACK_ELEM y)
{
    if (strcmp(x.elem, y.elem) < 0)
    {
        push(s, y);
        free(x.elem);
        return 1;
    }
    else
    {
        push(s, x);
        free(y.elem);
        return 1;
    }
    return 0;
}

/**
 * @brief Função de operação maior de dois valores do topo da stack.
 *
 *  É comparado o token com o caracter ' e> ':
 *  - Se for igual então guarda os dois valores no topo da stack nas variaveis x e y, com o auxilio de uma condição verifica o tipo de x e usa uma função auxiliar para determinar qual o maior elemento.
 *  - Retorna 1 se a operação foi executada com sucesso, caso contrario retorna 0.
 * @param[in] s Recebe um apontador para a stack.
 * @param[in] token Recebe um token.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param STACK_ELEM x - Guarda o primeiro valor do topo da stack com o auxilio da função pop.
 * @param STACK_ELEM y - Guarda o segundo valor do topo da stack com o auxilio da função pop.
 * @param Function maiorCondInt(s, x, y) - Função auxiliar da função maiorCond(Função caso x seja um inteiro).
 * @param Function maiorCondDbl(s, x, y) - Função auxiliar da função maiorCond(Função caso x seja um double).
 * @param Function maiorCondChar(s, x, y) - Função auxiliar da função maiorCond(Função caso x seja um caractere).
 * @param Function maiorCondString(s, x, y) - Função auxiliar da função maiorCond(Função caso x seja uma string).
 */
int maiorCond(STACK *s, char *token)
{
    if (strcmp(token, "e>") == 0)
    {
        STACK_ELEM y = pop(s);
        STACK_ELEM x = pop(s);
        if (x.t == INT)
        {
            return maiorCondInt(s, x, y);
        }
        else if (x.t == DBL)
        {
            return maiorCondDbl(s, x, y);
        }
        else if (x.t == CHAR)
        {
            return maiorCondChar(s, x, y);
        }
        else
        {
            return maiorCondString(s, x, y);
        }
    }
    return 0;
}

/**
 * @brief Função de operação ifThenElse dos três valores do topo da stack.
 *
 *  É comparado o token com o caracter ' ? ':
 *  - Se for igual guarda os três elementos no topo da stack nas variaveis x, y e z, verifica se x é verdadeiro, se for faz push de y para a stack, caso contrario faz push de z. No fim devolve 1 à função conditionalHandle.
 *  - Se não for igual então retorna 0 à função conditionalHandle.
 * @param[in] s Recebe um apontador para a stack.
 * @param[in] token Recebe um token.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param STACK_ELEM x - Guarda o terceiro valor do topo da stack com o auxilio da função pop.
 * @param STACK_ELEM y - Guarda o segundo valor do topo da stack com o auxilio da função pop.
 * @param STACK_ELEM z - Guarda o primeiro valor do topo da stack com o auxilio da função pop.
 * @param function push(s, y) - Guarda no topo da stack o elemento y, no caso de x ser verdadeiro.
 * @param function push(s, z) - Guarda no topo da stack o elemento z, no caso de x ser falso.
 */
int ifThenElse(STACK *s, char *token)
{
    if (strcmp(token, "?") == 0)
    {
        STACK_ELEM z = pop(s);
        STACK_ELEM y = pop(s);
        STACK_ELEM x = pop(s);
        if (x.t == INT && *(long *)x.elem != 0)
        {
            push(s, y);
            free(x.elem);
            free(z.elem);
            return 1;
        }
        else if (x.t == DBL && *(double *)x.elem != 0)
        {
            push(s, y);
            free(x.elem);
            free(z.elem);
            return 1;
        }
        else if (x.t == CHAR && *(char *)x.elem != 0)
        {
            push(s, y);
            free(x.elem);
            free(z.elem);
            return 1;
        }
        else if (x.t == ARR && (*(STACK *)x.elem).sp != 0)
        {
            push(s, y);
            free(x.elem);
            free(z.elem);
            return 1;
        }
        else
        {
            push(s, z);
            free(x.elem);
            free(y.elem);
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Função conditional Handle que chama as funções de operações de logica condicional.
 *
 * @param[in] s Recebe um apontador para a stack.
 * @param[in] token Recebe um token.
 * @retval 1 se foi executada com êxito.
 * @retval 0 se não foi executada com êxito.
 * @param Function eCond(s, token) - Função de operação e&(Condicional).
 * @param Function ouCond(s, token) - Função de operação e|(Condicional).
 * @param Function menorCond(s, token) - Função de operação menor de dois valores do topo da stack.
 * @param Function maiorCond(s, token) - Função de operação maior de dois valores do topo da stack.
 * @param Function ifThenElse(s, token) - Função de operação ifThenElse dos três valores do topo da stack.
 */
int conditionalHandle(STACK *s, char *token)
{
    return (eCond(s, token) || ouCond(s, token) || menorCond(s, token) || maiorCond(s, token) || ifThenElse(s, token));
}