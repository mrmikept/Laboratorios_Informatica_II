#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stack.h"

/**
 * @file variables.c
 * @brief Ficheiro variables.c que contém todas as funções relativas as váriaveis.
 */

/**
 * @brief Função que popula o array variables[VAR_NUMB] com os valores por omissão das váriaveis.
 *
 * Primeiramente popula o array a -1, de seguida dá os valores por omissão ás variaveis de A a F, S, N e de X a Z, criando sempre referências novas para os elementos e guardando o var.t com o tipo correto do elemento.
 * @param[in] s - Recebe um apontador para a stack.
 * @param STACK_ELEM var - Variavel do tipo STACK_ELEM onde é guardado o apontador para o respetivo elemento e o TYPE t correto.
 * @param void *IntPT - Apontador void com o tamanho para um long.
 * @param void *charPtS - Apontador void com o tamanho de um char para alocar o char Space ' '.
 * @param void *charPtN - Apontador void com o tamanho de um char para alocar o char de mudança de linha '\n'.
 */
STACK_ELEM *varValues()
{
    int i;
    STACK_ELEM *variables = malloc(sizeof(STACK_ELEM) * 26);
    for (i = 0; i < 26; i++) // Tudo a -1
    {
        STACK_ELEM var;
        void *IntPT = malloc(sizeof(long));
        *(long *)IntPT = -1;
        var.elem = IntPT;
        var.t = INT;
        variables[i] = var;
    }
    for (i = 0; i < 6; i++) // De A até F = 10(incrementando);
    {
        STACK_ELEM var;
        void *IntPT = malloc(sizeof(long));
        *(long *)IntPT = i + 10;
        var.elem = IntPT;
        var.t = INT;
        variables[i] = var;
    }

    STACK_ELEM var;
    void *charPtS = malloc(sizeof(char)); // Space ' '
    *(char *)charPtS = ' ';
    var.elem = charPtS;
    var.t = CHAR;
    variables['S' - 'A'] = var;

    void *charPtN = malloc(sizeof(char)); // New Line '\n'
    *(char *)charPtN = '\n';
    var.elem = charPtN;
    var.t = CHAR;
    variables['N' - 'A'] = var;

    for (i = 23; i != VAR_NUMB; i++) // X = 0; Y = 1; Z = 2;
    {
        STACK_ELEM var;
        void *IntPT = malloc(sizeof(long));
        *(long *)IntPT = i - 23;
        var.elem = IntPT;
        var.t = INT;
        variables[i] = var;
    }
    return variables;
}

/**
 * @brief Função que coloca o valor da váriavel no topo da stack.
 *
 * É verificado se o token é um char que esteja entre os caracteres 'A' e 'Z'. Se sim ele determina o indice da Variavel(Código ASCII da letra - 65(Valor ASCII do char 'A')), verifica o tipo do elemento da váriavel e cria um apontador void com o tamanho do tipo do elemento, cópia o elemento para o apontador e faz push para a stack do valor e retorna 1 à função varHandle.
 * Caso contrario devolve 0 à função varHandle.
 * @param[in] s - Recebe um apontador para a stack.
 * @param[in] token - Recebe um token.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param STACK_ELEM res - Váriavel do tipo STACK_ELEM para guardar o apontador do elemento e o respetivo tipo.
 * @param int indVar - Variavel que determina o indice do array respetivo a letra recebida no token.
 * @param void *IntPt - Apontador void com o tamanho de um long.
 * @param void *dblPt - Apontador void com o tamanho de um double.
 * @param void *charPt - Apontador void com o tamanho de um char.
 * @param Function push(s, res) - Coloca no topo da stack o novo elemento.
 */
int varToStack(STACK *s, char *token)
{
    if (token[0] >= 'A' && token[0] <= 'Z')
    {
        STACK_ELEM res;
        int indVar = token[0] - 65;
        if (s->variables[indVar].t == INT)
        {
            void *IntPt = malloc(sizeof(long));
            *(long *)IntPt = *(long *)s->variables[indVar].elem;
            res.t = INT;
            res.elem = IntPt;
            push(s, res);
            return 1;
        }
        if (s->variables[indVar].t == DBL)
        {
            void *dblPt = malloc(sizeof(double));
            *(double *)dblPt = *(double *)s->variables[indVar].elem;
            res.t = DBL;
            res.elem = dblPt;
            push(s, res);
            return 1;
        }
        if (s->variables[indVar].t == CHAR)
        {
            void *charPt = malloc(sizeof(char));
            *(char *)charPt = *(char *)s->variables[indVar].elem;
            res.t = CHAR;
            res.elem = charPt;
            push(s, res);
            return 1;
        }
        if (s->variables[indVar].t == STR)
        {
            STACK_ELEM var = s->variables[indVar];
            int strsize = strlen(var.elem) + 1;
            char *string_copy = malloc(sizeof(char) * strsize);
            strcpy(string_copy, var.elem);
            res.t = STR;
            res.elem = string_copy;
            push(s, res);
            return 1;
        }
        if (s->variables[indVar].t == BLK)
        {
            STACK_ELEM var = s->variables[indVar];
            int strsize = strlen(var.elem) + 1;
            char *string_copy = malloc(sizeof(char) * strsize);
            strcpy(string_copy, var.elem);
            res.t = BLK;
            res.elem = string_copy;
            push(s, res);
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Função que cópia o valor do topo da stack para uma váriavel.
 *
 * Primeiro compara o token com o char ' : ' e verifica se o elemento a seguir é uma letra de 'A' a 'Z'. Se for cópia o elemento do topo da stack com o auxilio da função pop(s) e guarda-o na posição do array da letra respectiva, no fim retorna 1 à função varHandle.
 * Caso contrário retorna 0 à função varHandle.
 * @param[in] s - Recebe um apontador para a stack.
 * @param[in] token - Recebe um token.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param STACK_ELEM stackTop - Com o auxilio da função pop(s), copia o valor do topo da stack.
 * @param STACK_ELEM varcopy - Váriavel usada para guardar a cópia do elemento do topo da stack.
 * @param int varInd - Variavel que determina o indice do array respetivo a letra recebida no token.
 * @param Function pop(s) - Retira o elemento do topo da stack.
 * @param Function push(s, stackTop) - Volta a colocar o elemento retirado no topo da stack.
 */
int putValVar(STACK *s, char *token)
{
    if (token[0] == ':' && token[1] >= 'A' && token[1] <= 'Z')
    {
        STACK_ELEM stackTop = pop(s);
        STACK_ELEM varcopy;
        if (stackTop.t == INT)
        {
            void *intPt = malloc(sizeof(long));
            *(long *)intPt = *(long *)stackTop.elem;
            varcopy.t = INT;
            varcopy.elem = intPt;
        }
        else if (stackTop.t == DBL)
        {
            void *dblPt = malloc(sizeof(double));
            *(double *)dblPt = *(double *)stackTop.elem;
            varcopy.t = DBL;
            varcopy.elem = dblPt;
        }
        else if (stackTop.t == CHAR)
        {
            void *charPt = malloc(sizeof(char));
            *(double *)charPt = *(char *)stackTop.elem;
            varcopy.t = CHAR;
            varcopy.elem = charPt;
        }
        else if (stackTop.t == ARR)
        {
            void *arrayPt = malloc(sizeof(STACK));
            *(STACK *)arrayPt = *(STACK *)stackTop.elem;
            varcopy.t = ARR;
            varcopy.elem = arrayPt;
        }
        else if (stackTop.t == BLK)
        {
            int strsize = strlen(stackTop.elem) + 1;
            char *copy_string = malloc(sizeof(char) * strsize);
            strcpy(copy_string, stackTop.elem);
            varcopy.t = BLK;
            varcopy.elem = copy_string;
        }
        else
        {
            int strsize = strlen(stackTop.elem) + 1;
            char *copy_string = malloc(sizeof(char) * strsize);
            strcpy(copy_string, stackTop.elem);
            varcopy.t = STR;
            varcopy.elem = copy_string;
        }
        push(s, stackTop);
        int varInd = token[1] - 65;
        free(s->variables[varInd].elem);
        s->variables[varInd] = varcopy;
        return 1;
    }
    return 0;
}

/**
 * @brief Função Variable Handle que chama as funções de operações sobre variáveis.
 *
 * @param[in] s Recebe um apontador para a stack.
 * @param[in] token Recebe um token.
 * @retval 1 se foi executada com êxito.
 * @retval 0 se não foi executada com êxito.
 * @param Function varToStack(s, token) - Função que coloca o valor da váriavel no topo da stack.
 * @param Function putValVar(s, token) - Função que cópia o valor do topo da stack para uma váriavel.
 */
int varHandle(STACK *s, char *token)
{
    return (varToStack(s, token) || putValVar(s, token));
}