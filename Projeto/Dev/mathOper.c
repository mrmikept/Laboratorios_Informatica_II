/**
 * @file mathOper.c
 * @brief Ficheiro mathOper.c que contém todas as funções relativas a operações matemáticas entre valores.
 */
#include <stdlib.h>
#include <math.h>
#include "stack.h"

/**
 * @brief Função de adição de dois valores do topo da stack.
 *
 *  É verificado o tipo dos dois elementos recebidos como argumento, cria um novo elemento com o resultado da soma dos elementos, liberta a memória alocada para os elementos somados e faz push do resultado para a stack.
 *  Se foi possível concluir a operção retorna 1, caso contrario retorna 0.
 * @param[in] STACK *s - Recebe um apontador para a stack.
 * @param[in] STACK_ELEM x - Recebe um elemento x.
 * @param[in] STACK_ELEM y - Recebe um elemento y.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param STACK_ELEM res - Guarda o resultado da adição de x e y.
 * @param void *intPt - Apontador void com o tamanho de um long para a soma de inteiros.
 * @param void *dblPt - Apontador void com o tamanho de um double para a soma de doubles.
 * @param function push(s, res) - Guarda no topo da stack o resultado da soma de x e y.
 */
int addVal(STACK *s, STACK_ELEM x, STACK_ELEM y)
{
    if (x.t == INT && y.t == INT)
    {
        STACK_ELEM res;
        void *intPt = malloc(sizeof(long));
        *(long *)intPt = *((long *)x.elem) + *((long *)y.elem);
        res.elem = intPt;
        res.t = INT;
        push(s, res);
        free(x.elem);
        free(y.elem);
        return 1;
    }
    else
    {
        STACK_ELEM res;
        void *dblPt = malloc(sizeof(double));
        if (x.t == INT)
        {
            *(double *)dblPt = (*((long *)x.elem)) + (*((double *)y.elem));
        }
        else if (y.t == INT)
        {
            *(double *)dblPt = (*((double *)x.elem)) + (*((long *)y.elem));
        }
        else
        {
            *(double *)dblPt = (*((double *)x.elem)) + (*((double *)y.elem));
        }
        res.elem = dblPt;
        res.t = DBL;
        push(s, res);
        free(x.elem);
        free(y.elem);
        return 1;
    }
    return 0;
}

/**
 * @brief Função de subtração de dois valores do topo da stack.
 *
 *  É verificado o tipo dos dois elementos recebidos como argumento, cria um novo elemento com o resultado da subtração dos elementos, liberta a memória alocada para os elementos subtraidos e faz push do resultado para a stack.
 *  Se foi possível concluir a operção retorna 1, caso contrario retorna 0.
 * @param[in] STACK *s - Recebe um apontador para a stack.
 * @param[in] STACK_ELEM x - Recebe um elemento x.
 * @param[in] STACK_ELEM y - Recebe um elemento y.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param STACK_ELEM res - Guarda o resultado da subtração de x e y.
 * @param void *intPt - Apontador void com o tamanho de um long para a subtração de inteiros.
 * @param void *dblPt - Apontador void com o tamanho de um double para a subtração de doubles.
 * @param function push(s, res) - Guarda no topo da stack o resultado da subtração de x e y.
 */

int sub(STACK *s, STACK_ELEM x, STACK_ELEM y)
{
    if (x.t == INT && y.t == INT)
    {
        STACK_ELEM res;
        void *intPt = malloc(sizeof(long));
        *(long *)intPt = *((long *)y.elem) - *((long *)x.elem);
        res.elem = intPt;
        res.t = INT;
        push(s, res);
        free(x.elem);
        free(y.elem);
        return 1;
    }
    else if (x.t == DBL || y.t == DBL)
    {
        STACK_ELEM res;
        void *dbl = malloc(sizeof(double));
        if (x.t == INT)
        {
            *(double *)dbl = *((double *)y.elem) - *((long *)x.elem);
        }
        else if (y.t == INT)
        {
            *(double *)dbl = *((long *)y.elem) - *((double *)x.elem);
        }
        else
        {
            *(double *)dbl = *((double *)y.elem) - *((double *)x.elem);
        }
        res.elem = dbl;
        res.t = DBL;
        push(s, res);
        free(x.elem);
        free(y.elem);
        return 1;
    }
    return 0;
}

/**
 * @brief Função de multiplicação de dois valores do topo da stack.
 *
 *  É verificado o tipo dos dois elementos recebidos como argumento, cria um novo elemento com o resultado da multiplicação dos elementos, liberta a memória alocada para os elementos multiplicados e faz push do resultado para a stack.
 *  Se foi possível concluir a operção retorna 1, caso contrario retorna 0.
 * @param[in] STACK *s - Recebe um apontador para a stack.
 * @param[in] STACK_ELEM x - Recebe um elemento x.
 * @param[in] STACK_ELEM y - Recebe um elemento y.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param STACK_ELEM res - Guarda o resultado da multiplicação de x e y.
 * @param void *intPt - Apontador void com o tamanho de um long para a multiplicação de inteiros.
 * @param void *dblPt - Apontador void com o tamanho de um double para a multiplicação de doubles.
 * @param function push(s, res) - Guarda no topo da stack o resultado da multiplicação de x e y.
 */
int mult(STACK *s, STACK_ELEM x, STACK_ELEM y)
{
    if (x.t == INT && y.t == INT)
    {
        STACK_ELEM res;
        void *intPt = malloc(sizeof(long));
        *(long *)intPt = *((long *)x.elem) * *((long *)y.elem);
        res.elem = intPt;
        res.t = INT;
        push(s, res);
        free(x.elem);
        free(y.elem);
        return 1;
    }
    else if (x.t == DBL || y.t == DBL)
    {
        STACK_ELEM res;
        void *dblPt = malloc(sizeof(double));
        if (x.t == INT)
        {
            *(double *)dblPt = *((long *)x.elem) * *((double *)y.elem);
        }
        else if (y.t == INT)
        {
            *(double *)dblPt = *((double *)x.elem) * *((long *)y.elem);
        }
        else
        {
            *(double *)dblPt = *((double *)x.elem) * *((double *)y.elem);
        }
        res.elem = dblPt;
        res.t = DBL;
        push(s, res);
        free(x.elem);
        free(y.elem);
        return 1;
    }
    return 0;
}



/**
 * @brief Função de divisão de dois valores do topo da stack.
 *
 *  É verificado o tipo dos dois elementos recebidos como argumento, cria um novo elemento com o resultado da divisão dos elementos recebidos, liberta a memória alocada para os elementos divididos e faz push do resultado para a stack.
 *  Se foi possível concluir a operção retorna 1, caso contrario retorna 0.
 * @param[in] STACK *s - Recebe um apontador para a stack.
 * @param[in] STACK_ELEM x - Recebe um elemento x.
 * @param[in] STACK_ELEM y - Recebe um elemento y.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param STACK_ELEM res - Guarda o resultado da divisão de x e y.
 * @param void *intPt - Apontador void com o tamanho de um long para a divisão de inteiros.
 * @param void *dblPt - Apontador void com o tamanho de um double para a divisão de doubles.
 * @param function push(s, res) - Guarda no topo da stack o resultado da divisão de y por x.
 */
int divd(STACK *s, STACK_ELEM x, STACK_ELEM y)
{

    if (x.t == INT && y.t == INT)
    {
        STACK_ELEM res;
        void *intPt = malloc(sizeof(long));
        *(long *)intPt = *((long *)y.elem) / *((long *)x.elem);
        res.elem = intPt;
        res.t = INT;
        push(s, res);
        free(x.elem);
        free(y.elem);
        return 1;
    }
    else if (x.t == DBL || y.t == DBL)
    {
        STACK_ELEM res;
        void *dbl = malloc(sizeof(double));
        if (x.t == INT)
        {
            *(double *)dbl = *((double *)y.elem) / *((long *)x.elem);
        }
        else if (y.t == INT)
        {
            *(double *)dbl = *((long *)y.elem) / *((double *)x.elem);
        }
        else
        {
            *(double *)dbl = *((double *)y.elem) / *((double *)x.elem);
        }
        res.elem = dbl;
        res.t = DBL;
        push(s, res);
        free(x.elem);
        free(y.elem);
        return 1;
    }

    return 0;
}

/**
 * @brief Função de decremento do valor do topo da stack
 *
 *  É verificado o tipo do elemento x recebido como argumento, cria um novo elemento com o resultado da decrementação, liberta a memória alocada para o elemento recebido e faz push do resultado para a stack.
 *  Se foi possível concluir a operção retorna 1, caso contrario retorna 0.
 * @param[in] STACK *s - Recebe um apontador para a stack.
 * @param[in] STACK_ELEM x - Recebe um elemento x.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param void *intPt - Apontador void com o tamanho de um long para a decrementação de inteiros.
 * @param void *dblPt - Apontador void com o tamanho de um double para a decrementação de doubles.
 * @param void *CharPt - Apontador void com o tamanho de um char para a decrementação de char's.
 * @param function push(s, res) - Guarda no topo da stack o resultado da decrementação de x.
 */
int dec(STACK *s, STACK_ELEM x)
{
    if (x.t == INT)
    {
        STACK_ELEM res;
        void *intPt = malloc(sizeof(long));
        *(long *)intPt = *((long *)x.elem) - 1;
        res.elem = intPt;
        res.t = INT;
        push(s, res);
        free(x.elem);
        return 1;
    }
    else if (x.t == DBL)
    {
        STACK_ELEM res;
        void *dbl = malloc(sizeof(double));
        *(double *)dbl = *((double *)x.elem) - 1;
        res.elem = dbl;
        res.t = DBL;
        push(s, res);
        free(x.elem);
        return 1;
    }
    else
    {
        STACK_ELEM res;
        void *charPt = malloc(sizeof(char));
        *(char *)charPt = (char)(*(long *)x.elem - 1);
        res.t = CHAR;
        res.elem = charPt;
        push(s, res);
        free(x.elem);
        return 1;
    }
    return 0;
}



/**
 * @brief Função de incremento do valor do topo da stack
 *
 *  É verificado o tipo do elemento x recebido como argumento, cria um novo elemento com o resultado da incrementação, liberta a memória alocada para o elemento recebido e faz push do resultado para a stack.
 *  Se foi possível concluir a operção retorna 1, caso contrario retorna 0.
 * @param[in] STACK *s - Recebe um apontador para a stack.
 * @param[in] STACK_ELEM x - Recebe um elemento x.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param void *intPt - Apontador void com o tamanho de um long para a decrementação de inteiros.
 * @param void *dblPt - Apontador void com o tamanho de um double para a decrementação de doubles.
 * @param void *CharPt - Apontador void com o tamanho de um char para a decrementação de char's.
 * @param function push(s, res) - Guarda no topo da stack o resultado da incrementação de x.
 */
int inc(STACK *s, STACK_ELEM x)
{
    if (x.t == INT)
    {
        STACK_ELEM res;
        void *intPt = malloc(sizeof(long));
        *(long *)intPt = *((long *)x.elem) + 1;
        res.elem = intPt;
        res.t = INT;
        push(s, res);
        free(x.elem);
        return 1;
    }
    else if (x.t == DBL)
    {
        STACK_ELEM res;
        void *dbl = malloc(sizeof(double));
        *(double *)dbl = *((double *)x.elem) + 1;
        res.elem = dbl;
        res.t = DBL;
        push(s, res);
        free(x.elem);
        return 1;
    }
    else
    {
        STACK_ELEM res;
        void *charPt = malloc(sizeof(char));
        *(char *)charPt = (char)(*(long *)x.elem + 1);
        res.t = CHAR;
        res.elem = charPt;
        push(s, res);
        free(x.elem);
        return 1;
    }
    return 0;
}


/**
 * @brief Função de operação modulo de dois valores do topo da stack.
 *
 *  É verificado o tipo dos dois elementos recebidos como argumento, cria um novo elemento com o resultado do resto da divisão dos elementos recebidos, liberta a memória alocada para os elementos recebidos e faz push do resultado para a stack.
 *  Se foi possível concluir a operção retorna 1, caso contrario retorna 0.
 * @param[in] STACK *s - Recebe um apontador para a stack.
 * @param[in] STACK_ELEM x - Recebe um elemento x.
 * @param[in] STACK_ELEM y - Recebe um elemento y.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param STACK_ELEM res - Guarda o resultado da operação modulo de x e y.
 * @param void *intPt - Apontador void com o tamanho de um long para a divisão de inteiros.
 * @param function push(s, res) - Guarda no topo da stack o resultado do resto da divisão de x por y.
 */
int modulo(STACK *s, STACK_ELEM x, STACK_ELEM y)
{
    if (x.t == INT && y.t == INT)
    {
        STACK_ELEM res;
        void *intPt = malloc(sizeof(long));
        *(long *)intPt = *((long *)x.elem) % *((long *)y.elem);
        res.elem = intPt;
        res.t = INT;
        push(s, res);
        free(x.elem);
        free(y.elem);
        return 1;
    }
    return 0;
}





/**
 * @brief Função de exponenciação de dois valores do topo da stack.
 *
 *  É verificado o tipo de expon e base de forma a fazer a Type Cast do apontador void de forma correta e com o auxilio da função push coloca no topo da stack o resultado da exponenciação de x com y e liberta a mémoria alocada para expon e base.
 *  Se foi possível concluir a operão retorna 1, caso contrario retorna 0.
 * @param[in] s - Recebe um apontador para a stack.
 * @param[in] STACK_ELEM expon - Recebe um elemento expon(expoente).
 * @param[in] STACK_ELEM base - Recebe um elemento base.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param STACK_ELEM res_elem - Guarda o resultado da exponenciação.
 * @param int res - Guarda o resultado da exponenciação da base pelo expon no caso de serem inteiros.
 * @param double res - Guarda o resultado na exponenciação da base pelo expon no caso de serem doubles.
 * @param void *intPt - Apontador void com o tamanho de um long para a exponenciação de inteiros.
 * @param void *dblPt - Apontador void com o tamanho de um double para a exponenciação de doubles.
 * @param function push(s, res) - Guarda no topo da stack o resultado da exponenciação da base pelo expon.
 */
int expo(STACK *s, STACK_ELEM base, STACK_ELEM expon)
{
    if (expon.t == INT && base.t == INT)
    {
        int res = 1;
        for (int i = 0; i < *((long *)expon.elem); i++)
        {
            res *= *((long *)base.elem);
        }
        STACK_ELEM res_elem;
        void *intPt = malloc(sizeof(int));
        *(long *)intPt = res;
        res_elem.elem = intPt;
        res_elem.t = INT;
        push(s, res_elem);
        free(expon.elem);
        free(base.elem);
        return 1;
    }
    else if (expon.t == DBL || base.t == DBL)
    {
        STACK_ELEM res_elem;
        void *dblPt = malloc(sizeof(double));
        double res;
        if (expon.t == INT)
        {
            res = pow(*(double *)base.elem, (double)(*(long *)expon.elem));
        }
        else if (base.t == INT)
        {
            res = pow((double)(*(long *)base.elem), *(double *)expon.elem);
        }
        else
        {
            res = pow(*(double *)base.elem, *(double *)expon.elem);
        }
        *(double *)dblPt = res;
        res_elem.elem = dblPt;
        res_elem.t = DBL;
        push(s, res_elem);
        free(expon.elem);
        free(base.elem);
        return 1;
    }
    return 0;
}
