/**
 * @file strings.c
 * @brief Ficheiro strings.c que contém todas as funções relativas a operações em strings.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stack.h"

/**
 * @brief Cria uma linha para as strings.
 *
 * É comparado o token com o character ' \ ':
 * - Se for igual então verifica de que tipo é o elemento no topo da stack de forma a poder fazer type cast correto para inteiro. No fim faz push da variavel stackTOP com a conversão para inteiro do elemento e retorna 1 À função parseHandle.
 * - Se não for igual retorna 0 à função parseHandle.
 * @param[in] s - Recebe um apontador para a stack.
 * @param[in] token - Recebe um token.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param Function return stringline - Coloca no topo da stack o valor da conversão.
 */
char *getStringLine(char **line)
{
    int i = 0, s = 0;
    for (i = 0; (*line)[i] != '\"'; i++)
    {
        s++;
    }
    char *stringline = malloc(sizeof(char) * (s + 1));
    for (i = 0; i <= s; i++)
    {
        stringline[i] = (*line)[0];
        (*line)++;
    }
    (*line)++;
    stringline[s] = '\0';
    return stringline;
}

int createString(STACK *s, char **line)
{
    if (*line[0] == '"')
    {
        (*line)++;
        char *stringline = getStringLine(line);
        STACK_ELEM stringElem;
        stringElem.t = STR;
        stringElem.elem = stringline;
        push(s, stringElem);
        return 1;
    }
    return 0;
}

/**
 * @brief Separa a string por subStrings.
 *
 * É comparado o token com o character ' / ':
 * - Se for igual então verifica de que tipo é o elemento no topo da stack de forma a poder fazer type cast correto para inteiro. No fim faz push da variavel stackTOP com a conversão para inteiro do elemento e retorna 1 À função parseHandle.
 * - Se não for igual retorna 0 à função stringsHandle.
 * @param[in] s - Recebe um apontador para a stack.
 * @param[in] token - Recebe um token.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param void *intPt - Apontador void com o tamanho de um long.
 * @param STACK_ELEM stackTOP - Com o auxilio da função pop guarda o elemento que está no topo da stack.
 * @param Function push(s, stackTOP) - Coloca no topo da stack o valor da conversão.
 */
int subStringSep(STACK *s, STACK_ELEM x, STACK_ELEM y)
{
    if (x.t == STR && y.t == STR)
    {
        STACK_ELEM arrayE;
        STACK_ELEM stringE;
        STACK *array = new_Array(s);
        char *sep = y.elem;
        char *string_sep;
        string_sep = strtok(x.elem, sep);
        while (string_sep != NULL)
        {
            int str_size = strlen(string_sep) + 1;
            char *string = malloc(sizeof(char) * str_size);
            strcpy(string, string_sep);
            stringE.t = STR;
            stringE.elem = string;
            push(array, stringE);
            string_sep = strtok(NULL, sep);
        }
        void *arrayPt = malloc(sizeof(STACK));
        *(STACK *)arrayPt = *(STACK *)array;
        arrayE.t = ARR;
        arrayE.elem = arrayPt;
        push(s, arrayE);
        free(x.elem);
        free(y.elem);
        return 1;
    }

    return 0;
}

/**
 * @brief Separa a string por newLines.
 *
 * É comparado o token com o character ' N/ ':
 * - Se for igual então separa a string por newLines. No fim faz push do elemento arrayE  e retorna 1 À função stringHandle.
 * - Se não for igual retorna 0 à função stringHandle.
 * @param[in] s - Recebe um apontador para a stack.
 * @param[in] token - Recebe um token.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param void *arrayPt - Apontador void com o tamanho de uma stack.
 * @param STACK_ELEM x - Recebe o primeiro elemento da stack com a função pop.
 * @param STACK_ELEM arrayE - Guarda o resultado da função.
 * @param STACK_ELEM stringE - É utilizado para ajudar com as operações.
 * @param STACK *array - Cria um novo array.
 * @param Function push(s, arrayE) - Coloca no topo da stack o valor da conversão.
 */
int newLineSep(STACK *s, char *token)
{
    if (token[0] == 'N' && token[1] == '/' && token[2] == '\0')
    {
        STACK_ELEM x = pop(s);
        STACK_ELEM arrayE;
        STACK_ELEM stringE;
        STACK *array = new_Array(s);
        char *sep = "\n";
        char *string_sep;
        string_sep = strtok(x.elem, sep);
        while (string_sep != NULL)
        {
            int str_size = strlen(string_sep) + 1;
            char *string = malloc(sizeof(char) * str_size);
            strcpy(string, string_sep);
            stringE.t = STR;
            stringE.elem = string;
            push(array, stringE);
            string_sep = strtok(NULL, sep);
        }
        void *arrayPt = malloc(sizeof(STACK));
        *(STACK *)arrayPt = *(STACK *)array;
        arrayE.t = ARR;
        arrayE.elem = arrayPt;
        push(s, arrayE);
        // free(x.elem);
        return 1;
    }

    return 0;
}

/**
 * @brief Separa a string por whiteSpaces.
 *
 * É comparado o token com o character ' S/ ':
 * - Se for igual então separa a string por whitespaces. No fim faz push do elemento arrayE  e retorna 1 À função stringHandle.
 * - Se não for igual retorna 0 à função stringHandle.
 * @param[in] s - Recebe um apontador para a stack.
 * @param[in] token - Recebe um token.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param void *arrayPt - Apontador void com o tamanho de uma stack.
 * @param STACK_ELEM x - Recebe o primeiro elemento da stack com a função pop.
 * @param STACK_ELEM arrayE - Guarda o resultado da função.
 * @param STACK_ELEM stringE - É utilizado para ajudar com as operações.
 * @param STACK *array - Cria um novo array.
 * @param Function push(s, arrayE) - Coloca no topo da stack o valor da conversão.
 */
int whiteSpacesSep(STACK *s, char *token)
{
    if (token[0] == 'S' && token[1] == '/' && token[2] == '\0')
    {
        STACK_ELEM x = pop(s);
        STACK_ELEM arrayE;
        STACK_ELEM stringE;
        STACK *array = new_Array(s);
        for (char *p = x.elem; *p; p++)
        {
            if (*p == '\n')
            {
                *p = ' ';
            }
        }
        char *sep = " ";
        char *string_sep;
        string_sep = strtok(x.elem, sep);
        while (string_sep != NULL)
        {
            int str_size = strlen(string_sep) + 1;
            char *string = malloc(sizeof(char) * str_size);
            strcpy(string, string_sep);
            stringE.t = STR;
            stringE.elem = string;
            push(array, stringE);
            string_sep = strtok(NULL, sep);
        }
        void *arrayPt = malloc(sizeof(STACK));
        *(STACK *)arrayPt = *(STACK *)array;
        arrayE.t = ARR;
        arrayE.elem = arrayPt;
        push(s, arrayE);
        free(x.elem);
        return 1;
    }
    return 0;
}

/**
 * @brief Função auxiliar buscind que procura dentro de uma string o elemento de um indice e o devolve para a stack.
 *
 * Utilizamos uma condição para saber se x é inteiro:
 * - Se sim, x é o indice.
 * - Se não, y é o indice.
 * @param[in] s - Recebe um apontador para a stack.
 * @param[in] x - Recebe o segundo elemento da stack.
 * @param[in] y - Recebe o primeiro elemento da stack.
 * @retval 1 se a função foi executada com sucesso.
 * @param void *string - Apontador void de tamanho de um char.
 * @param STACK_ELEM caract - Váriavel para guardar o resultado da operação.
 * @param Function strcpy(string, y.elem) - Guarda o string de y no apontador string.
 * @param Function strcpy(string, x.elem) - Guarda o string de x no apontador string.
 * @param Function push(s, caract) - Guarda no topo da stack o resultado da operação
 */
int buscaindstr(STACK *s, STACK_ELEM x, STACK_ELEM y)
{
    if (x.t == INT)
    {
        int indice = *(long *)x.elem;
        int size = strlen(y.elem) + 1;
        char *string = malloc(sizeof(char) * size);
        strcpy(string, y.elem);
        STACK_ELEM caract;
        caract.t = CHAR;
        void *charpt = malloc(sizeof(char));
        *(char *)charpt = string[indice];
        caract.elem = charpt;
        push(s, caract);
        free(x.elem);
        free(y.elem);
        return 1;
    }
    else
    {
        int indice = *(long *)y.elem;
        int size = strlen(x.elem) + 1;
        char *string = malloc(sizeof(char) * size);
        strcpy(string, x.elem);
        STACK_ELEM caract;
        caract.t = CHAR;
        void *charpt = malloc(sizeof(char));
        *(char *)charpt = string[indice];
        caract.elem = charpt;
        push(s, caract);
        free(x.elem);
        free(y.elem);
        return 1;
    }
    return 0;
}

/**
 * @brief Função para buscar o inicio de uma string.
 *
 * @param[in] s Recebe um apontador para a stack.
 * @param[in] x - Recebe o segundo elemento da stack.
 * @param[in] y - Recebe o primeiro elemento da stack.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param char *str - Copia a string x/y na string nova.
 * @param char *stringx - Apontador de tamanho char.
 * @param char *stringy - Apontador de tamanho char.
 * @param STACK_ELEM string - Cria string nova para fazer push a stack.
 * @param STACK_ELEM res - Cria inteiro para fazer push a stack.
 * @param Function push(s, string) - Função que coloca na stack o resultado da operação.
 * @param Function push(s, res) - Função que coloca na stack o resultado da operação.
 */
int buscinicioStr(STACK *s, STACK_ELEM x, STACK_ELEM y)
{
    if (x.t == STR && y.t == INT)
    {
        int size = *(long *)y.elem;
        char *stringx = malloc(sizeof(char) * size + 1);
        char *str = x.elem;
        for (int i = 0; i <= size; i++)
        {
            stringx[i] = str[i];
        }
        stringx[size] = '\0';
        STACK_ELEM string;
        string.t = STR;
        string.elem = stringx;
        push(s, string);
        free(x.elem);
        free(y.elem);
        return 1;
    }
    else
    {
        int size = *(long *)x.elem;
        char *stringy = malloc(sizeof(char) * size + 1);
        char *str = y.elem;
        for (int i = 0; i <= size; i++)
        {
            stringy[i] = str[i];
        }
        stringy[size] = '\0';
        STACK_ELEM string;
        string.t = STR;
        string.elem = stringy;
        push(s, string);
        free(x.elem);
        free(y.elem);
        return 1;
    }
}

/**
 * @brief Função para buscar o fim de uma string.
 *
 * @param[in] s Recebe um apontador para a stack.
 * @param[in] x - Recebe o segundo elemento da stack.
 * @param[in] y - Recebe o primeiro elemento da stack.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param char *str - Copia a string x/y na string nova.
 * @param char *new_string - Apontador de tamanho char.
 * @param char *stringy - Apontador de tamanho char.
 * @param STACK_ELEM string - Cria string nova para fazer push a stack.
 * @param STACK_ELEM res - Cria inteiro para fazer push a stack.
 * @param Function push(s, string) - Função que coloca na stack o resultado da operação.
 * @param Function push(s, res) - Função que coloca na stack o resultado da operação.
 */
int buscaFinalStr(STACK *s, STACK_ELEM x, STACK_ELEM y)
{
    if (x.t == STR && y.t == INT)
    {
        int i = 0;
        int size = *(long *)y.elem;
        int strleng = strlen(x.elem);
        int buff = strleng - size;
        char *new_string = malloc(sizeof(char) * size + 1);
        char *str = x.elem;
        for (i = 0; i <= size && buff <= strleng; i++)
        {
            new_string[i] = str[buff];
            buff++;
        }
        new_string[size] = '\0';
        STACK_ELEM string;
        string.t = STR;
        string.elem = new_string;
        push(s, string);
        free(x.elem);
        free(y.elem);
        return 1;
    }
    else if (x.t == INT && y.t == STR)
    {
        int i = 0;
        int size = *(long *)x.elem;
        int strleng = strlen(y.elem);
        int buff = strleng - size;
        char *new_string = malloc(sizeof(char) * size + 1);
        char *str = y.elem;
        for (i = 0; i <= size && buff <= strleng; i++)
        {
            new_string[i] = str[buff];
            buff++;
        }
        new_string[size] = '\0';
        STACK_ELEM string;
        string.t = STR;
        string.elem = new_string;
        push(s, string);
        free(x.elem);
        free(y.elem);
        return 1;
    }
    return 0;
}

/**
 * @brief Procura uma substring na string.
 *
 * @param[in] s - Recebe um apontador para a stack.
 * @param[in] sunstr - Recebe uma substring.
 * @param[in] string - Recebe uma string.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param void *intPt - Apontador void com o tamanho de um long.
 * @param char *res - Guarda o resultado da operação.
 * @param Function push(s, ind) - Coloca no topo da stack o valor do indice.
 */
int substring(STACK *s, STACK_ELEM substr, STACK_ELEM string)
{
    STACK_ELEM ind;
    char *substr1 = substr.elem;
    char *string1 = string.elem;
    char *res = strstr(string1, substr1);
    void *intPt = malloc(sizeof(long));
    if (res)
    {
        long string_size = strlen(string1);
        long substr_size = strlen(res);
        long indice = string_size - substr_size;
        *(long *)intPt = indice;
    }
    else
    {
        *(long *)intPt = -1;
    }
    ind.t = INT;
    ind.elem = intPt;
    push(s, ind);
    return 1;
}

/**
 * @brief Função auxiliar da função menor(Função caso seja uma string).
 *
 * Utilizamos uma condição para, com base no tipo de y, saber se x e y possuem o menor valor:
 * - Se sim, fazemos push de 1 para a stack.
 * - Se não, fazemos push de 0 para a stack.
 * @param[in] s - Recebe um apontador para a stack.
 * @param[in] x - Recebe o segundo elemento da stack.
 * @param[in] y - Recebe o primeiro elemento da stack.
 * @retval 1 se a função foi executada com sucesso.
 * @param void *intPt - Apontador void com o tamanho de um long.
 * @param STACK_ELEM res - Váriavel para guardar o resultado da operação.
 * @param Function push(s, res) - Guarda no topo da stack o resultado da operação
 */
int menorStr(STACK *s, STACK_ELEM x, STACK_ELEM y)
{
    if (x.t == STR && y.t == STR)
    {
        STACK_ELEM res;
        void *intPt = malloc(sizeof(long));
        if (strcmp(x.elem, y.elem) > 0)
        {
            *(long *)intPt = 0;
        }
        else
        {
            *(long *)intPt = 1;
        }
        res.t = INT;
        res.elem = intPt;
        push(s, res);
        free(x.elem);
        free(y.elem);
        return 1;
    }
    return 0;
}

/**
 * @brief Função auxiliar da função igual(Função caso seja uma string).
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
int igualStr(STACK *s, STACK_ELEM x, STACK_ELEM y)
{
    STACK_ELEM logicVal;
    logicVal.t = INT;
    void *intPt = malloc(sizeof(long));
    *(long *)intPt = 0;
    if (strcmp(x.elem, y.elem) == 0)
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
 * @brief Função auxiliar da função maior(Função caso seja uma string).
 *
 * Utilizamos uma condição para, com base no tipo de y, saber se x e y possuem o maior valor:
 * - Se sim, fazemos push de 1 para a stack.
 * - Se não, fazemos push de 0 para a stack.
 * @param[in] s - Recebe um apontador para a stack.
 * @param[in] x - Recebe o segundo elemento da stack.
 * @param[in] y - Recebe o primeiro elemento da stack.
 * @retval 1 se a função foi executada com sucesso.
 * @param void *intPt - Apontador void com o tamanho de um long.
 * @param STACK_ELEM res - Váriavel para guardar o resultado da operação.
 * @param Function push(s, res) - Guarda no topo da stack o resultado da operação
 */
int maiorStr(STACK *s, STACK_ELEM x, STACK_ELEM y)
{
    if (x.t == STR && y.t == STR)
    {
        STACK_ELEM res;
        void *intPt = malloc(sizeof(long));
        if (strcmp(x.elem, y.elem) < 0)
        {
            *(long *)intPt = 0;
        }
        else
        {
            *(long *)intPt = 1;
        }
        res.t = INT;
        res.elem = intPt;
        push(s, res);
        free(x.elem);
        free(y.elem);
        return 1;
    }
    return 0;
}

/**
 * @brief Função strings Handle que chama as funções de operações de strings.
 *
 * @param[in] s Recebe um apontador para a stack.
 * @param[in] token Recebe um token.
 * @retval 1 se foi executada com êxito.
 * @retval 0 se não foi executada com êxito.
 *
 * @param Function whiteSpacesSep(s,token) - Função de separar a string por whiteSpaces.
 * @param Function newLineSep(s,token) - Função de separar a string por newLines.
 */
int stringsHandle(STACK *s, char *token)
{
    return (whiteSpacesSep(s, token) || newLineSep(s, token));
}