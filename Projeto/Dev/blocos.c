#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "stack.h"
#include "operators.h"
#include "parse.h"
#include "Debug.h"

/**
 * @brief Função que guarda o conteúdo de um bloco numa string.
 *
 * - Com o auxílio de um ciclo e de uma variavel s, é determinado o numero de caracteres do bloco.
 * - Cria-se uma string com o tamanho de s+1(devido ao terminator caracter).
 * - Com o auxílio de mais um ciclo for é guardado os caracteres do bloco na string criada.
 * @param[in] char **line - Apontdor para uma string.
 * @return blockline - String com o conteúdo do bloco.
 * @param char *blockline - Declaração de uma string para guardar o conteúdo do bloco.
 */
char *getBlockLine(char **line)
{
    int i = 0, s = 0;
    for (i = 0; (*line)[i] != '}'; i++)
    {
        s++;
    }
    char *blockline = malloc(sizeof(char) * (s + 1));
    for (i = 0; i <= s; i++)
    {
        blockline[i] = (*line)[0];
        (*line)++;
    }
    (*line)++;
    blockline[s] = '\0';
    return blockline;
}

/**
 * @brief Função que cria um bloco.
 *
 * É comparado o primeiro caracter da string line com o caracter ' { ':
 * - Se for igual então incrementa a string line, com o auxilio da função getBlockLine guarda a string com o conteúdo do bloco, e é feito push dessa string para a stack como sendo um bloco.
 * @param[in] STACK *s - Apontador para a stack.
 * @param[in] char **line - Apontador para uma string.
 * @retval 1 se a operação foi executada com sucesso.
 * @retval 0 se a operação não foi executada com sucesso.
 * @param Function getBlockLine(line) - Função que guarda o conteúdo de um bloco numa string.
 * @param STACK_ELEM block - Elemento STACK_ELEM onde é atribuido o tipo de BLK e o apontador para o conteúdo do bloco.
 */
int createBlock(STACK *s, char **line)
{
    if (*line[0] == '{')
    {
        (*line)++;
        char *blockLine = getBlockLine(line);
        STACK_ELEM block;
        block.t = BLK;
        block.elem = blockLine;
        push(s, block);
        return 1;
    }
    return 0;
}

/**
 * @brief Função que executa um bloco.
 *
 * Com o auxilio de um ciclo e da função getToken, é feito parse da string com o conteúdo do bloco em tokens e depois é usado a função masterHandle para a analise dos tokens.
 * @param[in] STACK *s - Apontador para uma stack.
 * @param[in] STACK_ELEM x - Recebe um elemento do topo da stack.
 * @return 1 se a operação foi executada com sucesso.
 */
int executeBlock(STACK *s, STACK_ELEM x)
{
    char *line = x.elem;
    char *token;
    while (line[0] != '\0')
    {
        if (line[0] == ' ')
        {
            line++;
        }
        token = getToken(&line);
        masterHandle(s, token, &line);
    }
    return 1;
}

/**
 * @brief Função que executa um bloco sobre um array.
 *
 * Primeiro cria um novo array para guardar o resultado da execução das operações do bloco sobre o array, é usado um ciclo para analisar a string guardada no bloco e executar o seu conteúdo sobre cada elemento do array.
 * @param[in] STACK *s - Apontador para uma stack.
 * @param[in] STACK_ELEM b - Recebe um bloco.
 * @param[in] STACK_ELEM a - Recebe um array.
 * @param STACK array - Elemento para poder manusear o array.
 * @param STACK *exeArray - Array de STACK_ELEM para guardar o resultado das operações do bloco sobre o array.
 * @param STACK_ELEM newArray - Elemento para guardar o array resultado.
 * @param int maxSp - Valor do índice do elemento no fim do array.
 * @param Function new_Array(s) - Função que cria um novo elemento para a estrutura do array.
 * @param Function getToken(&line) - Função que separa a string line em token pelos espaços.
 * @param Function masterHandle - Função Master Handle que chama as restantes funções handle.
 * @return 1 se a operação foi executada com sucesso.
 */
int exeBlockArray(STACK *s, STACK_ELEM a, STACK_ELEM b)
{
    char *token;
    int i = 1;
    STACK array = *(STACK *)a.elem;
    STACK *exeArray = new_Array(s);
    STACK_ELEM newArray;
    int maxSp = array.sp;
    while (i <= maxSp)
    {
        push(exeArray, array.stack[i]);
        char *line = b.elem;
        while (line[0] != '\0')
        {
            token = getToken(&line);
            masterHandle(exeArray, token, &line);
        }
        i++;
    }
    void *arrayPt = malloc(sizeof(STACK));
    *(STACK *)arrayPt = *(STACK *)exeArray;
    newArray.t = ARR;
    newArray.elem = arrayPt;
    push(s, newArray);
    free(a.elem);
    return 1;
}

/**
 * @brief Função que executa um bloco sobre uma string.
 *
 * Primeiro cria um novo array para guardar o resultado da execução das operações do bloco sobre a string, é usado um ciclo para analisar a string guardada no bloco e executar o seu conteúdo sobre cada elemento do array e no fim copia todos os elementos do array para uma string.
 * @param[in] STACK *s - Apontador para uma stack.
 * @param[in] STACK_ELEM b - Recebe um bloco.
 * @param[in] STACK_ELEM a - Recebe um array.
 * @param STACK array - Elemento para poder manusear o array.
 * @param STACK *exeArray - Array de STACK_ELEM para guardar o resultado das operações do bloco sobre o array.
 * @param STACK_ELEM newArray - Elemento para guardar o array resultado.
 * @param int maxSp - Valor do índice do elemento no fim do array.
 * @param Function new_Array(s) - Função que cria um novo elemento para a estrutura do array.
 * @param Function getToken(&line) - Função que separa a string line em token pelos espaços.
 * @param Function masterHandle - Função Master Handle que chama as restantes funções handle.
 * @return 1 se a operação foi executada com sucesso.
 */
int exeBlockString(STACK *s, STACK_ELEM str, STACK_ELEM b)
{
    char *strbuff;
    char *token;
    strbuff = (str.elem);
    int i = 0;
    STACK *buffArray = new_Array(s);
    while (*(strbuff + i) != '\0')
    {
        STACK_ELEM charBuff;
        char test = *(strbuff + i);
        void *charPt = malloc(sizeof(char));
        *(char *)charPt = test;
        charBuff.t = CHAR;
        charBuff.elem = charPt;
        push(buffArray, charBuff);
        char *line = b.elem;
        while (line[0] != '\0')
        {
            token = getToken(&line);
            masterHandle(buffArray, token, &line);
        }
        i++;
    }
    int maxSp = buffArray->sp;
    char *newstring = malloc(sizeof(char) * maxSp);
    for (i = 1; i <= maxSp; i++)
    {
        char test = *(char *)buffArray->stack[i].elem;
        newstring[i - 1] = test;
    }
    newstring[maxSp] = '\0';
    STACK_ELEM string;
    string.t = STR;
    string.elem = newstring;
    push(s, string);
    return 1;
}

/**
 * @brief Função faz fold de um bloco sobre um array.
 *
 * Primeiro cria um novo array para guardar o resultado da execução das operações do bloco sobre o array, é usado um ciclo para analisar a string guardada no bloco e executar o seu conteúdo sobre cada elemento do array.
 * @param[in] STACK *s - Apontador para uma stack.
 * @param[in] STACK_ELEM b - Recebe um bloco.
 * @param[in] STACK_ELEM a - Recebe um array.
 * @param STACK array - Elemento para poder manusear o array.
 * @param STACK *exeArray - Array de STACK_ELEM para guardar o resultado das operações do bloco sobre o array.
 * @param STACK_ELEM newArray - Elemento para guardar o array resultado.
 * @param int maxSp - Valor do índice do elemento no fim do array.
 * @param Function new_Array(s) - Função que cria um novo elemento para a estrutura do array.
 * @param Function getToken(&line) - Função que separa a string line em token pelos espaços.
 * @param Function masterHandle - Função Master Handle que chama as restantes funções handle.
 * @return 1 se a operação foi executada com sucesso.
 */
int foldArrayBlock(STACK *s, STACK_ELEM a, STACK_ELEM b)
{
    char *token;
    int i = 1;
    STACK array = *(STACK *)a.elem;
    STACK *exeArray = new_Array(s);
    STACK_ELEM newArray;
    int maxSp = array.sp;
    push(exeArray, array.stack[1]);
    i++;
    while (i <= maxSp)
    {
        push(exeArray, array.stack[i]);
        char *line = b.elem;
        while (line[0] != '\0')
        {
            token = getToken(&line);
            masterHandle(exeArray, token, &line);
        }
        i++;
    }
    void *arrayPt = malloc(sizeof(STACK));
    *(STACK *)arrayPt = *(STACK *)exeArray;
    newArray.t = ARR;
    newArray.elem = arrayPt;
    push(s, newArray);
    free(a.elem);
    return 1;
}

/**
 * @brief Função que filtra um array por um bloco
 *
 * Primeiro cria um novo array para guardar o resultado da operação do bloco pelo array e depois verifica se os elementos do array resultante são verdadeiros ou falsos, e faz push para um novo array os elementos cujo resultado era verdadeiro. No fim faz push do array para a stack.
 * @param[in] STACK *s - Apontador para uma stack.
 * @param[in] STACK_ELEM b - Recebe um bloco.
 * @param[in] STACK_ELEM a - Recebe um array.
 * @return 1 se a operação foi executada com sucesso.
 */
int filterArrayBlock(STACK *s, STACK_ELEM a, STACK_ELEM b)
{
    char *token;
    int i = 1;
    STACK array = *(STACK *)a.elem;
    STACK *buff = new_Array(s);
    STACK *exeArray = new_Array(s);
    STACK_ELEM newArray;
    while (i <= array.sp)
    {
        STACK_ELEM elemBuff = array.stack[i];
        push(buff, elemBuff);
        char *line = b.elem;
        while (line[0] != '\0')
        {
            token = getToken(&line);
            masterHandle(buff, token, &line);
        }
        STACK_ELEM x = buff->stack[i];
        if (*(long *)x.elem != 0)
        {
            push(exeArray, array.stack[i]);
        }
        i++;
    }
    void *arrayPt = malloc(sizeof(STACK));
    *(STACK *)arrayPt = *(STACK *)exeArray;
    newArray.t = ARR;
    newArray.elem = arrayPt;
    push(s, newArray);
    free(a.elem);
    free(b.elem);
    free(buff->stack);
    return 1;
}

/**
 * @brief Função que filtra uma string por um bloco
 *
 * Primeiro cria um novo array para guardar o resultado da operação do bloco pela string e depois verifica se os elementos do array resultante são verdadeiros ou falsos, e faz push para uma nova string os elementos cujo resultado era verdadeiro. No fim faz push da string para a stack.
 * @param[in] STACK *s - Apontador para uma stack.
 * @param[in] STACK_ELEM b - Recebe um bloco.
 * @param[in] STACK_ELEM a - Recebe um array.
 * @return 1 se a operação foi executada com sucesso.
 */
int filterStringBlock(STACK *s, STACK_ELEM str, STACK_ELEM b)
{
    char *strbuff;
    char *token;
    strbuff = (str.elem);
    int i = 0;
    STACK *buffArray = new_Array(s);
    STACK *exeArray = new_Array(s);
    while (*(strbuff + i) != '\0')
    {
        STACK_ELEM charBuff;
        char test = *(strbuff + i);
        void *charPt = malloc(sizeof(char));
        *(char *)charPt = test;
        charBuff.t = CHAR;
        charBuff.elem = charPt;
        push(buffArray, charBuff);
        char *line = b.elem;
        while (line[0] != '\0')
        {
            token = getToken(&line);
            masterHandle(buffArray, token, &line);
        }
        STACK_ELEM x = buffArray->stack[i];
        if (*(long *)x.elem != 0)
        {
            push(exeArray, charBuff);
        }
        i++;
    }
    int maxSp = buffArray->sp;
    char *newstring = malloc(sizeof(char) * maxSp);
    for (i = 1; i <= maxSp; i++)
    {
        char test = *(char *)buffArray->stack[i].elem;
        newstring[i - 1] = test;
    }
    newstring[maxSp - 1] = '\0';
    STACK_ELEM string;
    string.t = STR;
    string.elem = newstring;
    push(s, string);
    return 1;
}

/**
 * @brief Função que faz filter de uma string/array por um bloco
 *
 * Primeiro faz pop do elemento no topo da stack, e verifica o seu tipo para chamar a função auxiliar de filter adequada.
 * @param[in] STACK *s - Apontador para uma stack.
 * @param[in] STACK_ELEM b - Recebe um bloco.
 * @param[in] STACK_ELEM a - Recebe um array.
 * @return 1 se a operação foi executada com sucesso.
 */
int filterBlock(STACK *s, STACK_ELEM b)
{
    STACK_ELEM y = pop(s);
    if (y.t == ARR)
    {
        return filterArrayBlock(s, y, b);
    }
    else
    {
        return filterStringBlock(s, y, b);
    }
}

/**
 * @brief Função que ordena um array pelo resultado da operação de um bloco.
 *
 * @param[in] STACK *s - Apontador para uma stack.
 * @param[in] STACK_ELEM b - Recebe um bloco.
 * @param[in] STACK_ELEM a - Recebe um array.
 * @return 1 se a operação foi executada com sucesso.
 */
int sortbyBlock(STACK *s, STACK_ELEM b)
{
    STACK_ELEM a = pop(s);
    char *token;
    int i = 1, j = 1;
    STACK array = *(STACK *)a.elem;
    STACK *buff = new_Array(s);
    STACK_ELEM newArray;
    while (i <= array.sp)
    {
        STACK_ELEM elemBuff = array.stack[i];
        push(buff, elemBuff);
        char *line = b.elem;
        while (line[0] != '\0')
        {
            token = getToken(&line);
            masterHandle(buff, token, &line);
        }
        i++;
    }
    int max = buff->sp;
    for (i = 1; i <= max; i++)
    {
        for (j = 1; j < max; j++)
        {
            if ((*(long *)(buff->stack[j]).elem) > (*(long *)(buff->stack[j + 1]).elem))
            {
                STACK_ELEM tempB = buff->stack[j];
                buff->stack[j] = buff->stack[j + 1];
                buff->stack[j + 1] = tempB;
                STACK_ELEM tempA = array.stack[j];
                array.stack[j] = array.stack[j + 1];
                array.stack[j + 1] = tempA;
            }
        }
    }

    void *arrayPt = malloc(sizeof(STACK));
    *(STACK *)arrayPt = array;
    newArray.t = ARR;
    newArray.elem = arrayPt;
    push(s, newArray);
    free(a.elem);
    free(buff);
    return 1;
}