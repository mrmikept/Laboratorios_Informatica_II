/**
 * @file stack.c
 * @brief Ficheiro que possui todas as funções de manuseamento da stack.
 */

/**
 * @brief Valor usado para defenir o tamanho máximo de uma stack.
 * 
 */
#define STACK_BUF 100

#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "arrays.h"
#include "variables.h"
#include "Debug.h"

/**
 * @brief Função que retorna um apontador para um array de STACK_ELEM para guardar os elementos na stack.
 * 
 * @param[in] STACK *s - Recebe um apontador para uma estrutura.
 * @param STACK_ELEM *stack - Apontador para um array de STACK_ELEM.
 * @return stack - Retorna um apontador para um array de STACK_ELEM.
 */
STACK_ELEM *new_Stack(STACK *s)
{
    STACK_ELEM *stack = malloc(sizeof *(s->stack) * STACK_BUF);
    return stack;
}

/**
 * @brief Função que cria uma main stack.
 *
 * É alocada memoria com o tamanho da estrutura STACK, inicia os valores das váriaveis com os valores por omissão, é alocado memoria para um array de STACK_ELEM para guardar os elementos, é iniciado o stackpointer a 0 e o size com o tamanho do STACK_BUF.
 * @param Function varValues(s) - Função para popular o array variables com os valores iniciais das váriaveis.
 * @param Function new_Stack(s) - Função que retorna um apontador para um array de STACK_ELEM para guardar os elementos na stack.
 * @return s - Apontador para a estrutura stack.
 */
STACK *new_MainStack()
{
    STACK *s = malloc(sizeof(STACK));
    STACK_ELEM *var = varValues();
    s->variables = var;
    STACK_ELEM *stack = new_Stack(s);
    s->stack = stack;
    s->size = STACK_BUF;
    s->sp = 0;
    return s;
}

/**
 * @brief Função que cria um array.
 *
 * É alocada memoria com o tamanho da estrutura STACK, é atribuido um apontador para o array com os valores das váriaveis da stack, é alocado memoria para um array de STACK_ELEM para guardar os elementos, é iniciado o stackpointer a 0 e o size com o tamanho do STACK_BUF.
 * @param Function varValues(s) - Função para popular o array variables com os valores iniciais das váriaveis.
 * @param Function new_Stack(s) - Função que retorna um apontador para um array de STACK_ELEM para guardar os elementos na stack.
 * @return a - Apontador para uma estrutura stack que simula uma stack.
 */
STACK *new_Array(STACK* s)
{
    STACK *a = malloc(sizeof(STACK));
    STACK_ELEM *var = s->variables;
    a->variables = var;
    STACK_ELEM *stack = new_Stack(a);
    a->stack = stack;
    a->size = STACK_BUF;
    a->sp = 0;
    return a;
}

/**
 * @brief Função que faz push de um novo elemento para o topo da stack.
 *
 * Verifica se o valor do apontador da stack é maior ou igual ao tamanho máximo alocado para a stack:
 * - Se for maior ou igual então cria um apontador para um array de STACK_ELEM, aumenta o tamanho máximo(s->size) com o valor de STACK_BUF, e com a função realloc aloca mais memoria. Se a função realloc não retornar NULL então atribui o novo apontador *a stack.
 * De seguida incrementa o apontador para a stack e coloca o valor da variavel elem no topo da stack.
 * @param[in] s Recebe um apontador para a stack
 * @param[in] elem Recebe um elemento a ser colocado no topo da stack.
 * @param STACK_ELEM *new_stackSize - Apontador para um array de STACK_ELEM.
 */
void push(STACK *s, STACK_ELEM elem)
{
    if (s->sp + 5 >= s->size)
    {
        s->size += STACK_BUF;
        STACK_ELEM *new_stackSize;
        new_stackSize = realloc(s->stack, (s->size) * sizeof *(s->stack));
        if (new_stackSize != NULL)
        {
            s->stack = new_stackSize;
        }
    }
    s->sp++;
    s->stack[s->sp] = elem;
}

/**
 * @brief Função que faz pop do elemento do topo da stack.
 *
 * Guarda o valor que esta no topo da stack na variavel ret e decrementa o apontador para a stack.
 * @param[in] s Recebe um apontador para a stack.
 * @return Valor da váriavel ret.
 * @param Var ret - Guarda o valor do topo da stack para depois ser retornado.
 */
STACK_ELEM pop(STACK *s)
{
    STACK_ELEM ret = s->stack[s->sp];
    s->sp--;
    return ret;
}

/**
 * @brief Função que faz print dos conteudos da stack.
 *
 * Função que faz print dos valores guardados na stack dependendo do tipo do elemento.
 * @param s
 */
void printStack(STACK *s)
{
    for (int i = 1; i <= s->sp; i++)
    {
        if (s->stack[i].t == CHAR)
        {
            printf("%c", *(char *)(s->stack[i].elem));
        }
        if (s->stack[i].t == INT)
        {
            printf("%ld", *(long *)(s->stack[i].elem));
        }
        if (s->stack[i].t == DBL)
        {
            printf("%g", *(double *)(s->stack[i].elem));
        }
        if (s->stack[i].t == ARR)
        {
            printArray(s->stack[i].elem);
        }
        if (s->stack[i].t == STR)
        {
            printf("%s", (char *)(s->stack[i].elem));
        }
        if (s->stack[i].t == BLK)
        {
            putchar('{');
            printf("%s", (char *)(s->stack[i].elem));
            putchar('}');
        }
    }
    printf("\n");
}