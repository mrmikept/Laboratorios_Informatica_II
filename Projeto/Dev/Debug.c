/**
 * @file Debug.c
 * @brief Ficheiro Debug.c que contém todas as funções relativas a operações de Debug.
 */
#include <stdio.h>
#include <string.h>
#include "stack.h"
#include "arrays.h"

/**
 * @brief Função que faz print dos elementos de um array.
 *
 * Função que faz print dos valores guardados em um array dependendo seu tipo.
 * @param[in] STACK *s - Recebe um apontador para um array.
 */
void printStackTopArray(STACK *s)
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
        if (s->stack[s->sp].t == STR)
        {
            printf("%s", (char *)(s->stack[s->sp].elem));
        }
        if (s->stack[i].t == ARR)
        {
            printStackTopArray(s->stack[i].elem);
        }
    }
}

/**
 * @brief Função que faz print do elemento no topo da stack.
 * 
 * É comparado o token com o caracter ' p ', se for igual então faz print do elemento no topo da stack.
 * Se foi possível concluir a operação retorna 1, caso contrario retorna 0.
 * @param[in] STACK *s - Recebe um apontador para a Stack. 
 * @param[in] char *token - Recebe uma string token.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possível executar a função.
 * @param Function printStackTopArray - Função que faz print dos elementos de um array.
 */
int printStackTop(STACK *s, char *token)
{
    if (strcmp(token, "p") == 0)
    {
        if (s->stack[s->sp].t == CHAR)
        {
            printf("%c", *(char *)(s->stack[s->sp].elem));
        }
        if (s->stack[s->sp].t == INT)
        {
            printf("%ld", *(long *)(s->stack[s->sp].elem));
        }
        if (s->stack[s->sp].t == DBL)
        {
            printf("%g", *(double *)(s->stack[s->sp].elem));
        }
        if (s->stack[s->sp].t == STR)
        {
            printf("%s", (char *)(s->stack[s->sp].elem));
        }
        if (s->stack[s->sp].t == ARR)
        {
            printStackTopArray(s->stack[s->sp].elem);
        }
        putchar('\n');
        return 1;
    }
    return 0;
}

/**
 * @brief Função que faz print dos elementos da stack referenciando o seu tipo e qual o valor do stackpointer desse elemento.
 * 
 * É comparado o token com o caracter ' pst ', se for igual então faz print dos elementos e dos referidos tipos da stack.
 * Se foi possível concluir a operação retorna 1, caso contrario retorna 0.
 * @param[in] STACK *s - Recebe um apontador para a Stack. 
 * @param[in] char *token - Recebe uma string token.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possível executar a função.
 * @param Function printStackTopArray - Função que faz print dos elementos de um array.
 */
int printSType(STACK *s, char *token)
{
    if (strcmp(token, "pst") == 0)
    {
        printf("Print de todos os elementos e respetivos tipos atualmente na stack:\n");
        for (int i = 1; i <= s->sp; i++)
        {
            if (s->stack[i].t == CHAR)
            {
                printf("%dº elemento: '%c', tipo: CHAR, stack pointer: %d\n", i, *(char *)(s->stack[i].elem), i);
            }
            if (s->stack[i].t == INT)
            {
                printf("%dº elemento: %ld, tipo: INT, stack pointer: %d\n", i, *(long *)(s->stack[i].elem), i);
            }
            if (s->stack[i].t == DBL)
            {
                printf("%dº elemento: %g, tipo: DBL, stack pointer: %d\n", i, *(double *)(s->stack[i].elem), i);
            }
            if (s->stack[i].t == STR)
            {
                printf("%dº elemento: \"%s\", tipo: STR, stack pointer: %d\n", i, (char *)(s->stack[i].elem), i);
            }
            if (s->stack[i].t == ARR)
            {
                printf("%dº elemento:", i);
                printStackTopArray(s->stack[i].elem);
                printf("tipo: ARR, numero de elementos: %d, stack pointer: %d\n",(*(STACK*)(s->stack[i].elem)).sp, i);
            }
        }
        printf("\n");
        return 1;
    }
    return 0;
}

/**
 * @brief Função que faz print de um STACK_ELEM recebido como argumento.
 * 
 * @param[in] elem - Recebe um elemento 
 */
void printElem(STACK_ELEM elem)
{
    printf("Elemento ");
    if (elem.t == CHAR)
    {
        printf("CHAR: %c\n", *(char *)(elem.elem));
    }
    if (elem.t == INT)
    {
        printf("INT: %ld\n", *(long *)(elem.elem));
    }
    if (elem.t == DBL)
    {
        printf("DOUBLE: %g\n", *(double *)(elem.elem));
    }
    if (elem.t == STR)
    {
        printf("STRING: \"%s\"\n", (char *)(elem.elem));
    }
    if (elem.t == ARR)
    {
        printStackTopArray(elem.elem);
        putchar('\n');
    }
}


/**
 * @brief Função debug Handle que chama as funções de operações de debug.
 *
 * @param[in] s Recebe um apontador para a stack.
 * @param[in] token Recebe um token.
 * @retval 1 se foi executada com êxito.
 * @retval 0 se não foi executada com êxito.
 * @param Function printSType(s, token) - Função que faz print dos elementos da stack referenciando o seu tipo e qual o valor do stackpointer desse elemento.
 * @param Function printStackTop(s, token) - Função que faz print do elemento no topo da stack.
 */
int debugHandle(STACK *s, char *token)
{
    return (printSType(s, token) || printStackTop(s, token));
}