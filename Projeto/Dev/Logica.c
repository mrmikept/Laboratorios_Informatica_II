/**
 * @file Logica.c
 * @brief Ficheiro Logica.c que contém todas as funções relativas a operações lógicas.
 */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "stack.h"

/**
 * @brief Função auxiliar da função igual(Função caso x seja um inteiro).
 *
 * Utilizamos uma condição para, com base no tipo de y, saber se x e y possuem o mesmo valor:
 * - Se sim, fazemos push de 1 para a stack.
 * - Se não, fazemos push de 0 para a stack.
 * @param[in] s - Recebe um apontador para a stack.
 * @param[in] x - Recebe o segundo elemento da stack.
 * @param[in] y - Recebe o primeiro elemento da stack.
 * @retval 1 se a função foi executada com sucesso.
 * @param void *intPt - Apontador void com o tamanho de um long.
 * @param STACK_ELEM logicVal - Váriavel para guardar o resultado da operação.
 * @param Function push(s, logicVal) - Guarda no topo da stack o resultado da operação
 */
int igualInt(STACK *s, STACK_ELEM x, STACK_ELEM y)
{
    STACK_ELEM logicVal;
    logicVal.t = INT;
    void *intPt = malloc(sizeof(long));
    *(long *)intPt = 0;
    if (y.t == INT && *(long *)x.elem == *(long *)y.elem)
    {
        *(long *)intPt = 1;
    }
    if (y.t == DBL && *(long *)x.elem == *(double *)y.elem)
    {
        *(long *)intPt = 1;
    }
    if (y.t == CHAR && *(long *)x.elem == (*(char *)y.elem))
    {
        *(long *)intPt = 1;
    }
    logicVal.elem = intPt;
    push(s, logicVal);
    free(x.elem);
    free(y.elem);
    return 1;
}

/**
 * @brief Função auxiliar da função igual(Função caso x seja um double).
 *
 * Utilizamos uma condição para, com base no tipo de y, saber se x e y possuem o mesmo valor:
 * - Se sim, fazemos push de 1 para a stack.
 * - Se não, fazemos push de 0 para a stack.
 * @param[in] s - Recebe um apontador para a stack.
 * @param[in] x - Recebe o segundo elemento da stack.
 * @param[in] y - Recebe o primeiro elemento da stack.
 * @retval 1 se a função foi executada com sucesso.
 * @param void *intPt - Apontador void com o tamanho de um long.
 * @param STACK_ELEM logicVal - Váriavel para guardar o resultado da operação.
 * @param Function push(s, logicVal) - Guarda no topo da stack o resultado da operação
 */
int igualDbl(STACK *s, STACK_ELEM x, STACK_ELEM y)
{
    STACK_ELEM logicVal;
    logicVal.t = INT;
    void *intPt = malloc(sizeof(long));
    *(long *)intPt = 0;
    if (y.t == DBL && *(double *)x.elem == *(double *)y.elem)
    {
        *(long *)intPt = 1;
    }
    if (y.t == INT && *(double *)x.elem == *(long *)y.elem)
    {
        *(long *)intPt = 1;
    }
    if (y.t == CHAR && *(double *)x.elem == *(char *)y.elem)
    {
        *(long *)intPt = 1;
    }
    logicVal.elem = intPt;
    push(s, logicVal);
    free(x.elem);
    free(y.elem);
    return 1;
}

/**
 * @brief Função auxiliar da função igual(Função caso x seja um char).
 *
 * Utilizamos uma condição para, com base no tipo de y, saber se x e y possuem o mesmo valor:
 * - Se sim, fazemos push de 1 para a stack.
 * - Se não, fazemos push de 0 para a stack.
 * @param[in] s - Recebe um apontador para a stack.
 * @param[in] x - Recebe o segundo elemento da stack.
 * @param[in] y - Recebe o primeiro elemento da stack.
 * @retval 1 se a função foi executada com sucesso.
 * @param void *intPt - Apontador void com o tamanho de um long.
 * @param STACK_ELEM logicVal - Váriavel para guardar o resultado da operação.
 * @param Function push(s, logicVal) - Guarda no topo da stack o resultado da operação
 */
int igualChar(STACK *s, STACK_ELEM x, STACK_ELEM y)
{
    STACK_ELEM logicVal;
    logicVal.t = INT;
    void *intPt = malloc(sizeof(long));
    *(long *)intPt = 0;
    if (y.t == CHAR && *(char *)x.elem == *(char *)y.elem)
    {
        *(long *)intPt = 1;
    }
    if (y.t == INT && *(char *)x.elem == *(long *)y.elem)
    {
        *(long *)intPt = 1;
    }
    if (y.t == DBL && *(char *)x.elem == *(double *)y.elem)
    {
        *(long *)intPt = 1;
    }
    logicVal.elem = intPt;
    push(s, logicVal);
    free(x.elem);
    free(y.elem);
    return 1;
}

/**
 * @brief Função de operação de igualdade lógica de dois valores do topo da stack.
 *
 * - Atraves de uma condição verifica o tipo de x e usa uma função auxiliar para determinar se x e y são iguais.
 * - Se foi possível concluir a operção retorna 1, caso contrario retorna 0.
 * @param[in] s Recebe um apontador para a stack.
 * @param[in] STACK_ELEM x - Recebe um elemento x.
 * @param[in] STACK_ELEM y - Recebe um elemento y.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param Function igualInt - Função auxiliar da função igual(Função caso x seja um inteiro).
 * @param Function igualDbl - Função auxiliar da função igual(Função caso x seja um double).
 * @param Function igualChar - Função auxiliar da função igual(Função caso x seja um char).
 */
int igualVal(STACK *s, STACK_ELEM x, STACK_ELEM y)
{
    if (x.t == INT)
    {
        return igualInt(s, x, y);
    }
    else if (x.t == DBL)
    {
        return igualDbl(s, x, y);
    }
    else if (x.t == CHAR)
    {
        return igualChar(s, x, y);
    }
    return 0;
}

/**
 * @brief Função auxiliar da função menor(Função caso x seja um inteiro).
 *
 * Utilizamos uma condição para, com base no tipo de y, saber se x é menor que y:
 * - Se sim, fazemos push de 1 para a stack.
 * - Se não, fazemos push de 0 para a stack.
 * @param[in] s - Recebe um apontador para a stack.
 * @param[in] x - Recebe o segundo elemento da stack.
 * @param[in] y - Recebe o primeiro elemento da stack.
 * @retval 1 se a função foi executada com sucesso.
 * @param void *intPt - Apontador void com o tamanho de um long.
 * @param STACK_ELEM logicVal - Váriavel para guardar o resultado da operação.
 * @param Function push(s, logicVal) - Guarda no topo da stack o resultado da operação
 */
int menorInt(STACK *s, STACK_ELEM x, STACK_ELEM y)
{
    STACK_ELEM logicVal;
    logicVal.t = INT;
    void *intPt = malloc(sizeof(long));
    *(long *)intPt = 0;
    if (y.t == INT && *(long *)x.elem < *(long *)y.elem)
    {
        *(long *)intPt = 1;
    }
    if (y.t == DBL && *(long *)x.elem < *(double *)y.elem)
    {
        *(long *)intPt = 1;
    }
    if (y.t == CHAR && *(long *)x.elem < (*(char *)y.elem))
    {
        *(long *)intPt = 1;
    }
    logicVal.elem = intPt;
    push(s, logicVal);
    free(x.elem);
    free(y.elem);
    return 1;
}

/**
 * @brief Função auxiliar da função menor(Função caso x seja um double).
 *
 * Utilizamos uma condição para, com base no tipo de y, saber se x é menor que y:
 * - Se sim, fazemos push de 1 para a stack.
 * - Se não, fazemos push de 0 para a stack.
 * @param[in] s - Recebe um apontador para a stack.
 * @param[in] x - Recebe o segundo elemento da stack.
 * @param[in] y - Recebe o primeiro elemento da stack.
 * @retval 1 se a função foi executada com sucesso.
 * @param void *intPt - Apontador void com o tamanho de um long.
 * @param STACK_ELEM logicVal - Váriavel para guardar o resultado da operação.
 * @param Function push(s, logicVal) - Guarda no topo da stack o resultado da operação
 */
int menorDbl(STACK *s, STACK_ELEM x, STACK_ELEM y)
{
    STACK_ELEM logicVal;
    logicVal.t = INT;
    void *intPt = malloc(sizeof(long));
    *(long *)intPt = 0;
    if (y.t == DBL && *(double *)x.elem < *(double *)y.elem)
    {
        *(long *)intPt = 1;
    }
    if (y.t == INT && *(double *)x.elem < *(long *)y.elem)
    {
        *(long *)intPt = 1;
    }
    if (y.t == CHAR && *(double *)x.elem < *(char *)y.elem)
    {
        *(long *)intPt = 1;
    }
    logicVal.elem = intPt;
    push(s, logicVal);
    free(x.elem);
    free(y.elem);
    return 1;
}

/**
 * @brief Função auxiliar da função menor(Função caso x seja um char).
 *
 * Utilizamos uma condição para, com base no tipo de y, saber se x é menor que y:
 * - Se sim, fazemos push de 1 para a stack.
 * - Se não, fazemos push de 0 para a stack.
 * @param[in] s - Recebe um apontador para a stack.
 * @param[in] x - Recebe o segundo elemento da stack.
 * @param[in] y - Recebe o primeiro elemento da stack.
 * @retval 1 se a função foi executada com sucesso.
 * @param void *intPt - Apontador void com o tamanho de um long.
 * @param STACK_ELEM logicVal - Váriavel para guardar o resultado da operação.
 * @param Function push(s, logicVal) - Guarda no topo da stack o resultado da operação
 */
int menorChar(STACK *s, STACK_ELEM x, STACK_ELEM y)
{
    STACK_ELEM logicVal;
    logicVal.t = INT;
    void *intPt = malloc(sizeof(long));
    *(long *)intPt = 0;
    if (y.t == CHAR && *(char *)x.elem < *(char *)y.elem)
    {
        *(long *)intPt = 1;
    }
    if (y.t == INT && *(char *)x.elem < *(long *)y.elem)
    {
        *(long *)intPt = 1;
    }
    if (y.t == DBL && *(char *)x.elem < *(double *)y.elem)
    {
        *(long *)intPt = 1;
    }
    logicVal.elem = intPt;
    push(s, logicVal);
    free(x.elem);
    free(y.elem);
    return 1;
}

/**
 * @brief Função de operação de menor lógico de dois valores do topo da stack.
 *
 *  Com o auxilio de uma condição verifica o tipo de x e usa uma função auxiliar para determinar se x é menor que y.
 *  Se foi possível concluir a operção retorna 1, caso contrario retorna 0.
 * @param[in] s Recebe um apontador para a stack.
 * @param[in] STACK_ELEM x - Recebe um elemento x.
 * @param[in] STACK_ELEM y - Recebe um elemento y.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param Function menorInt - Função auxiliar da função menor(Função caso x seja um inteiro).
 * @param Function menorDbl - Função auxiliar da função menor(Função caso x seja um double).
 * @param Function menorChar - Função auxiliar da função menor(Função caso x seja um char).
 */
int menorVal(STACK *s, STACK_ELEM x, STACK_ELEM y)
{
    if (x.t == INT)
    {
        return menorInt(s, x, y);
    }
    else if (x.t == DBL)
    {
        return menorDbl(s, x, y);
    }
    else if (x.t == CHAR)
    {
        return menorChar(s, x, y);
    }
    return 0;
}

/**
 * @brief Função auxiliar da função maior(Função caso x seja um inteiro).
 *
 * Utilizamos uma condição para, com base no tipo de y, saber se x é maior que y:
 * - Se sim, fazemos push de 1 para a stack.
 * - Se não, fazemos push de 0 para a stack.
 * @param[in] s - Recebe um apontador para a stack.
 * @param[in] x - Recebe o segundo elemento da stack.
 * @param[in] y - Recebe o primeiro elemento da stack.
 * @retval 1 se a função foi executada com sucesso.
 * @param void *intPt - Apontador void com o tamanho de um long.
 * @param STACK_ELEM logicVal - Váriavel para guardar o resultado da operação.
 * @param Function push(s, logicVal) - Guarda no topo da stack o resultado da operação
 */
int maiorInt(STACK *s, STACK_ELEM x, STACK_ELEM y)
{
    STACK_ELEM logicVal;
    logicVal.t = INT;
    void *intPt = malloc(sizeof(long));
    *(long *)intPt = 0;
    if (y.t == INT && *(long *)x.elem > *(long *)y.elem)
    {
        *(long *)intPt = 1;
    }
    if (y.t == DBL && *(long *)x.elem > *(double *)y.elem)
    {
        *(long *)intPt = 1;
    }
    if (y.t == CHAR && *(long *)x.elem > (*(char *)y.elem))
    {
        *(long *)intPt = 1;
    }
    logicVal.elem = intPt;
    push(s, logicVal);
    free(x.elem);
    free(y.elem);
    return 1;
}

/**
 * @brief Função auxiliar da função maior(Função caso x seja um double).
 *
 * Utilizamos uma condição para, com base no tipo de y, saber se x é maior que y:
 * - Se sim, fazemos push de 1 para a stack.
 * - Se não, fazemos push de 0 para a stack.
 * @param[in] s - Recebe um apontador para a stack.
 * @param[in] x - Recebe o segundo elemento da stack.
 * @param[in] y - Recebe o primeiro elemento da stack.
 * @retval 1 se a função foi executada com sucesso.
 * @param void *intPt - Apontador void com o tamanho de um long.
 * @param STACK_ELEM logicVal - Váriavel para guardar o resultado da operação.
 * @param Function push(s, logicVal) - Guarda no topo da stack o resultado da operação
 */
int maiorDbl(STACK *s, STACK_ELEM x, STACK_ELEM y)
{
    STACK_ELEM logicVal;
    logicVal.t = INT;
    void *intPt = malloc(sizeof(long));
    *(long *)intPt = 0;
    if (y.t == DBL && *(double *)x.elem > *(double *)y.elem)
    {
        *(long *)intPt = 1;
    }
    if (y.t == INT && *(double *)x.elem > *(long *)y.elem)
    {
        *(long *)intPt = 1;
    }
    if (y.t == CHAR && *(double *)x.elem > *(char *)y.elem)
    {
        *(long *)intPt = 1;
    }
    logicVal.elem = intPt;
    push(s, logicVal);
    free(x.elem);
    free(y.elem);
    return 1;
}

/**
 * @brief Função auxiliar da função maior(Função caso x seja um char).
 *
 * Utilizamos uma condição para, com base no tipo de y, saber se x é maior que y:
 * - Se sim, fazemos push de 1 para a stack.
 * - Se não, fazemos push de 0 para a stack.
 * @param[in] s - Recebe um apontador para a stack.
 * @param[in] x - Recebe o segundo elemento da stack.
 * @param[in] y - Recebe o primeiro elemento da stack.
 * @retval 1 se a função foi executada com sucesso.
 * @param void *intPt - Apontador void com o tamanho de um long.
 * @param STACK_ELEM logicVal - Váriavel para guardar o resultado da operação.
 * @param Function push(s, logicVal) - Guarda no topo da stack o resultado da operação
 */
int maiorChar(STACK *s, STACK_ELEM x, STACK_ELEM y)
{
    STACK_ELEM logicVal;
    logicVal.t = INT;
    void *intPt = malloc(sizeof(long));
    *(long *)intPt = 0;
    if (y.t == CHAR && *(char *)x.elem > *(char *)y.elem)
    {
        *(long *)intPt = 1;
    }
    if (y.t == INT && *(char *)x.elem > *(long *)y.elem)
    {
        *(long *)intPt = 1;
    }
    if (y.t == DBL && *(char *)x.elem > *(double *)y.elem)
    {
        *(long *)intPt = 1;
    }
    logicVal.elem = intPt;
    push(s, logicVal);
    free(x.elem);
    free(y.elem);
    return 1;
}

/**
 * @brief Função de operação de maior lógico de dois valores do topo da stack.
 *
 * - Com o auxilio de uma condição verifica o tipo de x e usa uma função auxiliar para determinar se x é maior que y.
 * - Se foi possível concluir a operção retorna 1, caso contrario retorna 0.
 * @param[in] s Recebe um apontador para a stack.
 * @param[in] STACK_ELEM x - Recebe um elemento x.
 * @param[in] STACK_ELEM y - Recebe um elemento y.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param Function maiorInt - Função auxiliar da função maior(Função caso x seja um inteiro).
 * @param Function maiorDbl - Função auxiliar da função maior(Função caso x seja um double).
 * @param Function maiorChar - Função auxiliar da função maior(Função caso x seja um char).
 */
int maiorVal(STACK *s, STACK_ELEM x, STACK_ELEM y)
{
    if (x.t == INT)
    {
        maiorInt(s, x, y);
        return 1;
    }
    else if (x.t == DBL)
    {
        maiorDbl(s, x, y);
        return 1;
    }
    else if (x.t == CHAR)
    {
        maiorChar(s, x, y);
        return 1;
    }
    return 0;
}

/**
 * @brief Função de operação de negação lógica do elemento do topo da stack.
 *
 * Com o auxilio de um condição é verificado o tipo da váriavel x recebida como argumento e é negado o seu valor(é inserido 0 na stack se x tiver valor de verdade, e 1 se x tiver valor de falsidade), no fim liberta a memoria alocada para a variavel x.
 *  Se foi possível concluir a operção retorna 1, caso contrario retorna 0.
 * @param[in] s Recebe um apontador para a stack.
 * @param[in] STACK_ELEM x - Recebe um elemento x.
 * @param[in] STACK_ELEM y - Recebe um elemento y.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param void *intPt - Apontador void com o tamanho de um long.
 * @param STACK_ELEM logicVal - Váriavel para guardar o resultado da operação.
 * @param Function push(s, logicVal) - Guarda no topo da stack o resultado da operação
 */
int negacao(STACK *s, STACK_ELEM x)
{
    STACK_ELEM logicVal;
    void *intPt = malloc(sizeof(long));
    if ((x.t == INT && *(long *)x.elem == 0) || (x.t == DBL && *(double *)x.elem == 0) || (x.t == CHAR && (long)(*(char *)x.elem) == 0))
    {
        *(long *)intPt = 1;
    }
    else
    {
        *(long *)intPt = 0;
    }
    logicVal.elem = intPt;
    logicVal.t = INT;
    push(s, logicVal);
    free(x.elem);
    return 1;
}
