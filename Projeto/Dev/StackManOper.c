/**
 * @file StackManOper.c
 * @brief Ficheiro StackManOper.c que contém todas as funções relativas a operações de manipulação da stack.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stack.h"
#include "parse.h"
#include "blocos.h"

/**
 * @brief Função de operação troca dos dois elementos do topo da stack.
 *
 *  É comparado o token com o caracter ' \ ':
 *  - Se for igual então guarda os dois valores no topo da stack nas variaveis x e y e com o auxilio da função push coloca no topo da stack a troca dos dois elementos e retorna 1 à função stackManipHandle.
 *  - Se não for igual então retorna 0 à função stackManipHandle.
 * @param[in] s Recebe um apontador para a stack.
 * @param[in] token Recebe um token.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param STACK_ELEM x - Guarda o primeiro valor do topo da stack com o auxilio da função pop.
 * @param STACK_ELEM y - Guarda o segundo valor do topo da stack com o auxilio da função pop.
 * @param function push - Guarda no topo da stack o resultado da troca dos dois elementos do topo da stack.
 */

int swapTopTwo(STACK *s, STACK_ELEM x, STACK_ELEM y)
{
        push(s, x);
        push(s, y);
        return 1;
}

/**
 * @brief Função de operação troca dos três elementos do topo da stack.
 *
 *  É comparado o token com o caracter ' @ ':
 *  - Se for igual então guarda os três valores no topo da stack nas variaveis x, y e z e com o auxilio da função push coloca no topo da stack a troca dos trẽs elementos e retorna 1 à função stackManipHandle.
 *  - Se não for igual então retorna 0 à função stackManipHandle.
 * @param[in] s Recebe um apontador para a stack.
 * @param[in] token Recebe um token.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param STACK_ELEM x - Guarda o primeiro valor do topo da stack com o auxilio da função pop.
 * @param STACK_ELEM y - Guarda o segundo valor do topo da stack com o auxilio da função pop.
 * @param STACK_ELEM z - Guarda o terceiro valor do topo da stack com o auxilio da função pop.
 * @param function push - Guarda no topo da stack o resultado da troca dos três elementos no topo da stack.
 */
int swapTopThree(STACK *s, STACK_ELEM x, STACK_ELEM y, STACK_ELEM z) // Rodar os 3 elementos no topo da stack com auxilio de 3 variaveis usando do pop e as ordenando corretamente usando o push.
{
        push(s, y);
        push(s, x);
        push(s, z);
        return 1;
}

/**
 * @brief Função que cópia o n-ésimo elemento para o topo da stack.
 *
 *  É comparado o token com o caracter ' $ ':
 *  - Se for igual então guarda o valor do topo da Stack na variável n, cópia o valor do apontador para o topo na stack no aponador spCopy e decrementa esse apontador n vezes, no fim com o auxilio da função push cópia o valor do n-ésimo elemento para o topo da stack e retorna 1 à função stackManipHandle.
 *  - Se não for igual então retorna 0 à função stackManipHandle.
 * @param[in] s Recebe um apontador para a stack.
 * @param[in] token Recebe um token.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param STACK_ELEM n - Guarda o valor do topo da stack com o auxilio da função pop.
 * @param STACK_ELEM copy - Guarda o valor da cópia do n-ésimo elemento da stack.
 * @param int spCopy - Cópia o valor do stack pointer.
 * @param function push(s, copy) - Guarda no topo da stack o resultado da operação e(bitwise) de x com y.
 */
int copyNElem(STACK *s, STACK_ELEM n)
{
    STACK_ELEM copy;
        int spCopy = s->sp;
        int i;
        for (i = 0; i < *(long *)n.elem; i++)
        {
            spCopy--;
        }
        if (s->stack[spCopy].t == INT)
        {
            void *intPt = malloc(sizeof(long));
            *(long *)intPt = *(long *)(s->stack[spCopy]).elem;
            copy.elem = intPt;
            copy.t = INT;
        }
        else if (s->stack[spCopy].t == DBL)
        {
            void *dblPt = malloc(sizeof(double));
            *(double *)dblPt = *(double *)(s->stack[spCopy]).elem;
            copy.elem = dblPt;
            copy.t = DBL;
        }
        else if (s->stack[spCopy].t == CHAR)
        {
            void *charPt = malloc(sizeof(char));
            *(char *)charPt = *(char *)(s->stack[spCopy]).elem;
            copy.elem = charPt;
            copy.t = CHAR;
        }
        else if (s->stack[spCopy].t == ARR)
        {
            STACK copy_array = *(STACK *)(s->stack[spCopy].elem);
            void *arrayPt = malloc(sizeof(STACK));
            *(STACK *)arrayPt = copy_array;
            copy.elem = arrayPt;
            copy.t = ARR;
        }
        else
        {
            int strleng = strlen(s->stack[spCopy].elem) + 1;
            char *copy_string = malloc(sizeof(char) * strleng);
            strcpy(copy_string, (s->stack[spCopy]).elem);
            copy.elem = copy_string;
            copy.t = STR;
        }
        push(s, copy);
        return 1;
}


/**
 * @brief Função que faz pop do elemento do topo da stack.
 *
 *  É comparado o token com o caracter ' ; ':
 *  - Se for igual então faz pop do elemento do topo da stack e retorna 1 à função stackManipHandle.
 *  - Se não for igual então retorna 0 à função stackManipHandle.
 * @param[in] s Recebe um apontador para a stack.
 * @param[in] token Recebe um token.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param pop(s) - Faz pop do elemento do topo da stack.
 */
int inPop(STACK *s, char *token) // Executa o pop no valor no topo da stack
{
    if (strcmp(token, ";") == 0)
    {
        STACK_ELEM x = pop(s);
        free(x.elem);
        free(token);
        return 1;
    }
    return 0;
}

/**
 * @brief Função de duplicação do elemento do topo da stack.
 *
 *  É comparado o token com o caracter ' _ ':
 *  - Se for igual então guarda o elemento do topo da stack na variavel x e com o auxilio da função push coloca no topo da stack a duplicação do elemento e retorna 1 à função stackManipHandle.
 *  - Se não for igual então retorna 0 à função stackManipHandle.
 * @param[in] s Recebe um apontador para a stack.
 * @param[in] token Recebe um token.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param STACK_ELEM x - Guarda o primeiro valor do topo da stack com o auxilio da função pop.
 * @param function push(s, x) - Guarda no topo da stack o resultado da operação e(bitwise) de x com y.
 */
int duplicate(STACK *s, char *token) // Duplica o elemento no topo da stack com o auxilio de uma variavel que guarda o seu valor e dois push's que duplicam o valor
{
    if (strcmp(token, "_") == 0)
    {
        STACK_ELEM x = pop(s);
        STACK_ELEM new_copy;
        if (x.t == INT)
        {
            void *intPt = malloc(sizeof(long));
            *(long *)intPt = *(long *)x.elem;
            new_copy.t = INT;
            new_copy.elem = intPt;
        }
        else if (x.t == DBL)
        {
            void *dblPt = malloc(sizeof(double));
            *(double *)dblPt = *(double *)x.elem;
            new_copy.t = DBL;
            new_copy.elem = dblPt;
        }
        else if (x.t == CHAR)
        {
            void *charPt = malloc(sizeof(char));
            *(char *)charPt = *(char *)x.elem;
            new_copy.t = CHAR;
            new_copy.elem = charPt;
        }
        else if (x.t == ARR)
        {
            void *arrayPt = malloc(sizeof(STACK));
            *(STACK *)arrayPt = *(STACK *)x.elem;
            new_copy.t = ARR;
            new_copy.elem = arrayPt;
        }
        else
        {
            int strsize = strlen(x.elem) + 1;
            char *new_string = malloc(sizeof(char) * strsize);
            strcpy(new_string, x.elem);
            new_copy.t = STR;
            new_copy.elem = new_string;
        }
        push(s, x);
        push(s, new_copy);
        free(token);
        return 1;
    }
    return 0;
}

/**
 * @brief Função ler uma linha
 *
 * É comparado o token com o caracter ' l ':
 * - Se for igual então usa a função fgets para ler uma linha do input stdin, guarda a string, na string lineRead, usa a função sscanf para retirar espaços e mudanças de linha.
 * Cria um apontador para uma string com o tamanho da string lineRead.
 * Cria um STACK_ELEM lineElem onde guarda o tipo como sendo uma string e guarda a referencia para o apontador line.
 * Faz push do lineElem para a stack.
 * - Caso contrario retorna 0 à função StackManipHandle.
 * @param s Recebe um apontador para a stack.
 * @param token Recebe um token.
 * @return 0 se a função não foi executada.
 * @return 1 se a função foi executada com sucesso.
 * @param char lineRead[BUFSIZE] - String para onde é guardada a string lida com o fgets.
 * @param char *line - apontador para a string lida
 * @param STACK_ELEM lineElem - Elemento onde é guardado o tipo e apontador da string lida.
 * @param function push(s, lineElem) - Guarda no topo da stack o elemento lineElem.
 */
int comandoL(STACK *s, char *token)
{
    if (strcmp(token, "l") == 0)
    {
        char lineRead[BUFSIZ];
        if (fgets(lineRead, BUFSIZ, stdin) != NULL)
        {
            char *line = malloc((strlen(lineRead) + 1) * sizeof(char));
            strcpy(line, lineRead);
            STACK_ELEM lineElem;
            lineElem.t = STR;
            lineElem.elem = line;
            push(s, lineElem);
        }
        return 1;
    }
    return 0;
}

/**
 * @brief Função ler todas as linhas.
 *
 * É comparado o token com o caracter ' t ':
 * - Se for igual então usa a função fgets para ler uma linha do input stdin, guarda a string, na string lineRead.
 * Cria um apontador para uma string com o tamanho da string lineRead.
 * Cria um STACK_ELEM res onde guarda o tipo como sendo uma string e guarda a referencia para o apontador line.
 * Faz push do res para a stack.
 * - Caso contrario retorna 0 à função StackManipHandle.
 * @param s Recebe um apontador para a stack.
 * @param token Recebe um token.
 * @return 0 se a função não foi executada.
 * @return 1 se a função foi executada com sucesso.
 * @param char lineRead[BUFSIZE] - String para onde é guardada a string lida com o fgets.
 * @param char *line - apontador para a string lida
 * @param STACK_ELEM res - Elemento onde é guardado o tipo e apontador da string lida.
 * @param function push(s, res) - Guarda no topo da stack o elemento res.
 */
int comandoT(STACK *s, char *token)
{
    if (strcmp(token, "t") == 0)
    {
        char lineRead[BUFSIZ];
        STACK_ELEM res;
        if (fgets(lineRead, BUFSIZ, stdin) != NULL)
        {
            int line_size = strlen(lineRead) + 1;
            char *line_buf;
            char *line = malloc(sizeof(char) * line_size);
            strcpy(line, lineRead);
            while (fgets(lineRead, BUFSIZ, stdin) != NULL)
            {

                line_size += strlen(lineRead);
                line_buf = realloc(line, line_size);
                line = line_buf;
                strcat(line, lineRead);
            }
            res.t = STR;
            res.elem = line;
            push(s, res);
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Função que insere valores na stack recebidos pelo input.
 *
 * Calcula o tamanho da string to token de forma a poder dar cast dos tipos corretos para o apontador void.
 * Com o recurso da função tokenType, identifica o tipo da string do token(intPtiro ou Double).
 * Cria um apontador void com o cast e tamanho correto para os diferentes Tipos.
 * Altera o valor da variavel val(do tipo STACK_ELEM) para o tipo correto e iguala o val.elem ao apontador void do elemento.
 * Faz push do val para Stack.
 * @param[in] s Recebe um apontador para a stack.
 * @param[in] token Recebe um token.
 * @return 1 se a função foi executada com sucesso.
 * @param STACK_ELEM val - Guarda o tipo do elemento recebido com o token e um apontador void para esse elemento.
 * @param char *str - Apontador criado para não partilhar a referencia do token de modo a poder guardar valores diferentes.
 * @param function tokenType - Identifica o tipo da string do token.
 * @param function push(s, val) - Guarda no topo da stack o elemento val.
 */
int val(STACK *s, char *token)
{
    if (token[0] == ' ' || token[0] == '\0')
    {
        return 1;
    }

    int tokenLength = strlen(token);

    STACK_ELEM val;

    char *str = malloc((tokenLength + 1) * sizeof(char));
    strcpy(str, token);

    val.t = tokenType(str, tokenLength);

    if (val.t == INT)
    {
        void *intPt = malloc(sizeof(long));
        sscanf(str, "%ld", (long *)intPt);
        val.elem = intPt;
    }
    else if (val.t == DBL)
    {
        void *dblPt = malloc(sizeof(double));
        sscanf(str, "%lf", (double *)dblPt);
        val.elem = dblPt;
    }
    else
    {
        val.elem = str;
    }
    push(s, val);
    free(token);
    return 1;
}

/**
 * @brief Função Stack Manipulation Handle que chama as funções de operações de manipulação da stack.
 *
 * @param[in] s Recebe um apontador para a stack.
 * @param[in] token Recebe um token.
 * @retval 1 se foi executada com êxito.
 * @retval 0 se não foi executada com êxito.
 *
 * @param Function swapTopTwo(s, token) - Função de operação troca dos dois elementos do topo da stack.
 * @param Function swapTopThree(s, token) - Função de operação troca dos três elementos do topo da stack.
 * @param Function duplicate(s, token) - Função de duplicação do elemento do topo da stack.
 * @param Function inPop(s, token) - Função que faz pop do elemento do topo da stack.
 * @param Function copyNElem(s, token) - Função que cópia o n-ésimo elemento para o topo da stack.
 * @param Function comandoL(s, token) - Função ler uma linha.
 * @param Function comandoT(s, token) - Função ler todas as linhas.
 * @param Function val(s, token) - Função que insere valores na stack recebidos pelo input.
 */
int stackManipHandle(STACK *s, char *token)
{
    return (comandoL(s, token) || comandoT(s, token) || val(s, token));
}
