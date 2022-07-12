/**
 * @file BitWOper.c
 * @brief Ficheiro BitWOper.c que contém todas as funções relativas a operações em bitwise de inteiros.
 */

#include <string.h>
#include <stdlib.h>
#include "stack.h"

/**
 * @brief Função de operação e(bitwise) dos dois valores do topo da stack.
 *
 *  É verificado o tipo dos dois elementos recebidos como argumento, cria um novo elemento com o resultado da operação e(bitwise) de x com y, liberta a memória alocada dos elementos recebidos e faz push do resultado para a stack.
 *  Se foi possível concluir a operção retorna 1, caso contrario retorna 0.
 * @param[in] s Recebe um apontador para a stack.
 * @param[in] STACK_ELEM x - Recebe um elemento x.
 * @param[in] STACK_ELEM y - Recebe um elemento y.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param STACK_ELEM res - Guarda o resultado da operação e(bitwise).
 * @param void *intPt - Apontador void com o tamanho para um inteiro.
 * @param function push(s, res) - Guarda no topo da stack o resultado da operação e(bitwise) de x com y.
 */

int andBitW(STACK *s, STACK_ELEM x, STACK_ELEM y)
{
    if (x.t == INT && y.t == INT)
    {
        int res = *((long *)x.elem) & *((long *)y.elem);
        STACK_ELEM res_elem;
        void *intPt = malloc(sizeof(long));
        *(long *)intPt = res;
        res_elem.elem = intPt;
        res_elem.t = INT;
        push(s, res_elem);
        free(x.elem);
        free(y.elem);
        return 1;
    }
    return 0;
}

/**
 * @brief Função de operação ou(bitwise) dos dois valores do topo da stack.
 *
 *  É verificado o tipo dos dois elementos recebidos como argumento, cria um novo elemento com o resultado da operação ou(bitwise) de x com y, liberta a memória alocada dos elementos recebidos e faz push do resultado para a stack.
 *  Se foi possível concluir a operção retorna 1, caso contrario retorna 0.
 * @param[in] s Recebe um apontador para a stack.
 * @param[in] STACK_ELEM x - Recebe um elemento x.
 * @param[in] STACK_ELEM y - Recebe um elemento y.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param STACK_ELEM res - Guarda o resultado da operação ou(bitwise).
 * @param void *intPt - Apontador void com o tamanho para um inteiro.
 * @param function push(s, res) - Guarda no topo da stack o resultado da operação ou(bitwise) de x com y.
 */
int orBitW(STACK *s, STACK_ELEM x, STACK_ELEM y)
{
    if (x.t == INT && y.t == INT)
    {
        int res = *((long *)x.elem) | *((long *)y.elem);
        STACK_ELEM res_elem;
        void *intPt = malloc(sizeof(long));
        *(long *)intPt = res;
        res_elem.elem = intPt;
        res_elem.t = INT;
        push(s, res_elem);
        free(x.elem);
        free(y.elem);
        return 1;
    }
    return 0;
}

/**
 * @brief Função de operação xor(bitwise) dos dois valores do topo da stack.
 *
 *  É verificado o tipo dos dois elementos recebidos como argumento, cria um novo elemento com o resultado da operação xor(bitwise) de x com y, liberta a memória alocada dos elementos recebidos e faz push do resultado para a stack.
 *  Se foi possível concluir a operção retorna 1, caso contrario retorna 0.
 * @param[in] s Recebe um apontador para a stack.
 * @param[in] STACK_ELEM x - Recebe um elemento x.
 * @param[in] STACK_ELEM y - Recebe um elemento y.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param STACK_ELEM res - Guarda o resultado da operação xor(bitwise).
 * @param void *intPt - Apontador void com o tamanho para um inteiro.
 * @param function push(s, res) - Guarda no topo da stack o resultado da operação xor(bitwise) de x com y.
 */
int xorBitW(STACK *s, STACK_ELEM x, STACK_ELEM y)
{
    if (x.t == INT && y.t == INT)
    {
        long res = (*((long *)x.elem)) ^ (*((long *)y.elem));
        STACK_ELEM res_elem;
        void *intPt = malloc(sizeof(long));
        *(long *)intPt = res;
        res_elem.elem = intPt;
        res_elem.t = INT;
        push(s, res_elem);
        free(x.elem);
        free(y.elem);
        return 1;
    }
    return 0;
}

/**
 * @brief Função de operação not(bitwise) do valor no topo da stack.
 *
 *  É verificado o tipo do elemento recebido como argumento, cria um novo elemento com o resultado da operação not(bitwise) de x, liberta a memória alocada do elemento recebido e faz push do resultado para a stack.
 *  Se foi possível concluir a operção retorna 1, caso contrario retorna 0.
 * @param[in] s Recebe um apontador para a stack.
 * @param[in] STACK_ELEM x - Recebe um elemento x.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param STACK_ELEM res - Guarda o valor da operação not(bitwise) de x.
 * @param void *intPt - Apontador void com o tamanho para um inteiro.
 * @param function push(s, res) - Guarda no topo da stack o resultado da operação not(bitwise) de x.
 */
int notBitW(STACK *s, STACK_ELEM x)
{
    if (x.t == INT)
    {
        long res = ~*((long *)x.elem);
        STACK_ELEM res_elem;
        void *intPt = malloc(sizeof(long));
        *(long *)intPt = res;
        res_elem.elem = intPt;
        res_elem.t = INT;
        push(s, res_elem);
        free(x.elem);
        return 1;
    }
    return 0;
}

