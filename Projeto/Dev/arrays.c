/**
 * @file arrays.c
 * @brief Ficheiro arrays.c que contém todas as funções relativas a operações em arrays.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "strings.h"
#include "parse.h"
#include "blocos.h"
#include "operators.h"
#include "Debug.h"

/**
 * @brief Função que faz print dos conteudos de um array.
 *
 * Função que faz print dos valores guardados num array dependendo do tipo do elemento.
 * @param[in] s - Recebe um apontador para um array(STACK).
 */
void printArray(STACK *a)
{
    for (int i = 1; i <= a->sp; i++)
    {
        if (a->stack[i].t == CHAR)
        {
            printf("%c", *(char *)(a->stack[i].elem));
        }
        if (a->stack[i].t == INT)
        {
            printf("%ld", *(long *)(a->stack[i].elem));
        }
        if (a->stack[i].t == DBL)
        {
            printf("%g", *(double *)(a->stack[i].elem));
        }
        if (a->stack[i].t == ARR)
        {
            printArray(a->stack[i].elem);
        }
        if (a->stack[i].t == STR)
        {
            printf("%s", (char *)a->stack[i].elem);
        }
    }
}


char *getArrayLine(char **line)
{
    char *arrayline = malloc(sizeof(char) * BUFSIZ);
    int i = 0, s = 0;
    int control = 1;
    for (i = 0; *line[0] != '\0' && control != 0; i++)
    {
        s++;
        arrayline[i] = *line[0];
        if (*line[0] == '[')
        {
            control++;
        }
        if (*line[0] == ']')
        {
            control--;
        }
        (*line)++;
    }
    (*line)++;
    arrayline[s] = '\0';
    char *result = malloc(sizeof(char) * s);
    strcpy(result, arrayline);
    return result;
}


int createArray(STACK *s, char *token, char **line)
{

    if (strcmp(token, "[") == 0)
    {
        char *arraytoken = malloc(sizeof(char) * BUFSIZ);
        char *arrayline = getArrayLine(line);
        STACK *a = new_Array(s);
        a->variables = s->variables;
        while (arrayline[0] != '\0')
        {
            if (arrayline[0] == '"')
            {
                createString(a, &arrayline);
            }
            else
            {

                if (arrayline[0] != ']')
                {
                    arraytoken = getToken(&arrayline);
                    masterHandle(a, arraytoken, &arrayline);
                }
                else
                {
                    arrayline = "";
                }
            }
        }
        void *arrayPt = malloc(sizeof(STACK_ELEM) * a->size);
        *(STACK *)arrayPt = *(STACK *)a;
        STACK_ELEM array;
        array.t = ARR;
        array.elem = arrayPt;
        push(s, array);
        return 1;
    }
    return 0;
}

/**
 * @brief Procura o tamanho de uma string ou array.
 *
 * É comparado o token com o character ' , ':
 * - Se for igual então verifica de que tipo é o elemento no topo da stack de forma a poder fazer a função. No fim faz push do tamanho da string ou array e retorna 1 À função arrayHandle.
 * - Se não for igual retorna 0 à função arrayHandle.
 * @param[in] s - Recebe um apontador para a stack.
 * @param[in] token - Recebe um token.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param STACK_ELEM x - Recebe o primeiro elemento da stack com ajuda da função pop.
 * @param STACK_ELEM y - Recebe o segundo elemento da stack com ajuda da função pop.
 * @param Function filterArrayBlocks - Envia para a função de blocos para filter.
 * @param STACK *array - Cria uma nova stack.
 * @param STACK_ELEM z - Cria um elemento para guardar o resultado na nova stack.
 * @param void *intpt - Apontador void de tamanho inteiro.
 * @param Function push(array, z) - Guarda o resultado na stack nova.
 * @param STACK_ELEM y - Elemento utilizado para guardar o resultado da função.
 * @param void *arraypt - Apontador void de tamanho de stack.
 * @param Function push(s, y) - Coloca no topo da stack o resultado da função.
 * @param STACK_ELEM z - Elemento utilizado para guardar o resultado da função.
 * @param Function push(s, z) - Coloca no topo da stack o resultado da função.
 * @param STACK_ELEM res - Elemento utilizado para guardar o resultado da função.
 * @param Function push(s, res) - Coloca no topo da stack o resultado da função.
 */
int range(STACK *s, STACK_ELEM x)
{
    if (x.t == INT)
    {
        STACK *array = new_Array(s);
        int i;
        int size = *(long *)x.elem;
        for (i = 0; i < size; i++)
        {
            STACK_ELEM z;
            void *intpt = malloc(sizeof(long));
            *(long *)intpt = i;
            z.elem = intpt;
            z.t = INT;
            push(array, z);
        }
        STACK_ELEM y;
        void *arraypt = malloc(sizeof(STACK));
        *(STACK *)arraypt = *(STACK *)array;
        y.t = ARR;
        y.elem = arraypt;
        push(s, y);
        return 1;
    }
    else if (x.t == ARR)
    {
        STACK array = *(STACK *)x.elem;
        int size = (array.sp);
        STACK_ELEM z;
        void *intpt = malloc(sizeof(long));
        *(long *)intpt = size;
        z.t = INT;
        z.elem = intpt;
        push(s, z);
        return 1;
    }
    else
    {
        int size = strlen(x.elem);
        STACK_ELEM res;
        void *intPt = malloc(sizeof(long));
        *(long *)intPt = size;
        res.elem = intPt;
        res.t = INT;
        push(s, res);
        return 1;
    }
    return 0;
}

int addtoArrayInc(STACK *s, STACK_ELEM a, STACK_ELEM y)
{
    if (y.t == ARR)
    {
        int i = 0;
        STACK arrayx = *(STACK *)a.elem;
        for (i = 1; i <= arrayx.sp; i++)
        {
            push(y.elem, arrayx.stack[i]);
        }
        push(s, y);
        return 1;
    }
    else if (y.t == STR)
    {
        push(a.elem, y);
        push(s, a);
        return 1;
    }
    else
    {
        int i = 0;
        STACK arrayx = *(STACK *)a.elem;
        int limit = arrayx.sp;
        STACK *array = new_Array(s);
        push(array, y);
        for (i = 1; i <= limit; i++)
        {
            push(array, arrayx.stack[i]);
        }
        STACK_ELEM res;
        void *arrayPt = malloc(sizeof(STACK));
        *(STACK *)arrayPt = *(STACK *)array;
        res.t = ARR;
        res.elem = arrayPt;
        push(s, res);
        free(a.elem);
        return 1;
    }
    return 0;
}

int addtoArrayFim(STACK *s, STACK_ELEM a, STACK_ELEM y)
{

    if (y.t == ARR)
    {
        int i = 0;
        STACK arrayx = *(STACK *)a.elem;
        for (i = 1; i <= arrayx.sp; i++)
        {
            push(y.elem, arrayx.stack[i]);
        }
        push(s, y);
        return 1;
    }
    else if (y.t == STR)
    {
        push(a.elem, y);
        push(s, a);
        return 1;
    }
    else
    {
        push(a.elem, y);
        push(s, a);
        return 1;
        return 1;
    }
    return 0;
}

int addtoString(STACK *s, STACK_ELEM x, STACK_ELEM y)
{
    if (x.t == STR && y.t == STR)
    {
        int strsize = strlen(x.elem) + strlen(y.elem) + 1;
        char *new_string = malloc(sizeof(char) * strsize);
        strcpy(new_string, y.elem);
        strcat(new_string, x.elem);
        STACK_ELEM new_Str;
        new_Str.t = STR;
        new_Str.elem = new_string;
        push(s, new_Str);
        return 1;
    }
    else if (y.t == STR)
    {
        strncat(y.elem, x.elem, 1);
        push(s, y);
        return 1;
    }
    else
    {
        int size = strlen(x.elem);
        char *string = malloc(sizeof(char) * size);
        strcpy(string, x.elem);
        memmove(string + 1, string, ++size);
        *string = *(char *)y.elem;
        x.elem = string;
        push(s, x);
        return 1;
    }
    return 0;
}

/**
 * @brief Função de adição de dois valores do topo da stack.
 *
 *  É comparado o token com o caracter ' + ':
 *  - Se for igual então guarda os dois valores no topo da stack nas variaveis x e y, é verificado o tipo de x e y de forma a fazer a Type Cast do apontador void de forma correta e com o auxilio da função push coloca no topo da stack o resultado da adição de x com y e retorna 1 à função MathHandle.
 *  - Se não for igual então retorna 0 à função MathHandle.
 * @param[in] s - Recebe um apontador para a stack.
 * @param[in] token - Recebe um token.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param STACK_ELEM x - Guarda o primeiro valor do topo da stack com o auxilio da função pop.
 * @param STACK_ELEM y - Guarda o segundo valor do topo da stack com o auxilio da função pop.
 * @param STACK_ELEM res - Guarda o resultado da adição de x e y.
 * @param void *intPt - Apontador void com o tamanho de um long para a soma de inteiros.
 * @param void *dblPt - Apontador void com o tamanho de um double para a soma de doubles.
 * @param function push(s, res) - Guarda no topo da stack o resultado da soma de x e y.
 */
int addArrayString(STACK *s, STACK_ELEM x, STACK_ELEM y)
{
    if (x.t == ARR)
    {
        return addtoArrayInc(s, x, y);
    }
    else if (y.t == ARR)
    {
        return addtoArrayFim(s, y, x);
    }
    else
    {
        return addtoString(s, x, y);
    }
    return 0;
}


int addarraynvezes(STACK *s, STACK_ELEM x, STACK_ELEM y)
{
    if (y.t == ARR)
    {
        int i = 0, j = 0;
        long rep = *(long *)x.elem;
        STACK array = *(STACK *)y.elem;
        STACK *newArray = new_Array(s);
        int maxSp = array.sp;
        for (i = 0; i < rep; i++)
        {
            for (j = 1; j <= maxSp; j++)
            {
                STACK_ELEM copy = array.stack[j];
                push(newArray, copy);
            }
        }
        void *arrayPt = malloc(sizeof(STACK));
        *(STACK *)arrayPt = *(STACK *)newArray;
        STACK_ELEM a;
        a.t = ARR;
        a.elem = arrayPt;
        push(s, a);
        free(y.elem);
        free(x.elem);
        return 1;
    }
    else if (y.t == STR)
    {
        int i = 0;
        char *copy = malloc(sizeof(char) * strlen(y.elem));
        strcpy(copy, y.elem);
        int rep = *(long *)x.elem;
        for (i = 1; i < rep; i++)
        {
            strcat(y.elem, copy);
        }
        push(s, y);
        free(copy);
        free(x.elem);
        return 1;
    }
    return 0;
}

/**
 * @brief Tira os elementos de uma stack.
 *
 * @param[in] s - Recebe um apontador para a stack.
 * @param[in] x - Recebe o primeiro elemento da stack.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param STACK array - Guarda a stack x num array novo.
 * @param STACK_ELEM arrayElem - Guarda o elemento da stack no array novo.
 * @param Function push(s, arrayElem) - Coloca no topo da stack o resultado da função.
 */
int tiraelementos(STACK *s, STACK_ELEM x) // token ~
{
    int i = 0;
    STACK array = *(STACK *)x.elem;
    int size = array.sp;
    for (i = 1; i <= size; i++)
    {
        STACK_ELEM arrayElem = array.stack[i];
        push(s, arrayElem);
    }
    free(x.elem);
    return 1;
}

/**
 * @brief Função auxiliar buscind que procura dentro de um array o elemento de um indice e o devolve para a stack.
 *
 * Utilizamos uma condição para saber se x e y são inteiros:
 * - Se sim, procuramos o indice do array.
 * - Se não, fazemos return 0.
 * @param[in] s - Recebe um apontador para a stack.
 * @param[in] x - Recebe o segundo elemento da stack.
 * @param[in] y - Recebe o primeiro elemento da stack.
 * @retval 1 se a função foi executada com sucesso.
 * @param STACK mid - Guarda o valor de y para poder dar o valor do indice.
 * @param STACK_ELEM res - Váriavel para guardar o resultado da operação.
 * @param Function push(s, res) - Guarda no topo da stack o resultado da operação
 */
int buscindArr(STACK *s, STACK_ELEM x, STACK_ELEM y) // Função auxiliar buscind que procura dentro de um array o elemento de um indice e o devolve para a stack.
{
    if (x.t == INT)
    {
        STACK mid = *(STACK *)y.elem;
        STACK_ELEM res = mid.stack[*(long *)x.elem + 1];
        push(s, res);
        free(x.elem);
        free(y.elem);
        return 1;
    }
    if (y.t == INT)
    {
        STACK mid = *(STACK *)x.elem;
        STACK_ELEM res = mid.stack[*(long *)y.elem + 1];
        push(s, res);
        free(x.elem);
        free(y.elem);
        return 1;
    }
    return 0;
}

/**
 * @brief Função para buscar o inicio de um array.
 *
 * @param[in] s Recebe um apontador para a stack.
 * @param[in] x - Recebe o segundo elemento da stack.
 * @param[in] y - Recebe o primeiro elemento da stack.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param STACK_ELEM z - É utilizado para guardar o resultado
 * @param STACK *temp - Cria uma nova stack.
 * @param STACK array - Copia o array x/y no array novo.
 * @param void *arraypt - Apontador void de tamanho STACK.
 * @param void *intPt - Apontador void de tamanho inteiro.
 * @param Function push(temp, z) - Função que coloca numa stack nova o resultado da operação.
 * @param Function push(s, z) - Função que coloca na stack o resultado da operação.
 */
int buscinicioArr(STACK *s, STACK_ELEM x, STACK_ELEM y)
{
    if (x.t == INT && y.t == ARR)
    {
        STACK_ELEM z;
        STACK *temp = new_Array(s);
        STACK array = *(STACK *)y.elem;
        int limit = *(long *)x.elem;
        int i = 1;
        while (i <= limit)
        {
            z = array.stack[i];
            push(temp, z);
            i++;
        }
        printStack(temp);
        void *arraypt = malloc(sizeof(STACK));
        *(STACK *)arraypt = *(STACK *)temp;
        z.elem = arraypt;
        z.t = ARR;
        push(s, z);
        free(x.elem);
        free(y.elem);
        return 1;
    }
    else
    {
        STACK_ELEM z;
        STACK *temp = new_Array(s);
        STACK array = *(STACK *)x.elem;
        int indice = *(long *)y.elem;
        int i = 1;
        while (i <= indice)
        {
            z = array.stack[i];
            push(temp, z);
            i++;
        }
        void *arraypt = malloc(sizeof(STACK));
        *(STACK *)arraypt = *(STACK *)temp;
        z.elem = arraypt;
        z.t = ARR;
        push(s, z);
        free(x.elem);
        free(y.elem);
        return 1;
    }
}

/**
 * @brief Função para buscar o fim de um array.
 *
 * @param[in] s Recebe um apontador para a stack.
 * @param[in] x - Recebe o segundo elemento da stack.
 * @param[in] y - Recebe o primeiro elemento da stack.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param STACK_ELEM z - É utilizado para guardar o resultado
 * @param STACK *temp - Cria uma nova stack.
 * @param STACK array - Copia o array x/y no array novo.
 * @param void *intPt - Apontador void de tamanho inteiro.
 * @param Function push(temp, z) - Função que coloca numa stack nova o resultado da operação.
 * @param Function push(s, z) - Função que coloca na stack o resultado da operação.
 */
int buscaFinalArr(STACK *s, STACK_ELEM x, STACK_ELEM y)
{
    if (x.t == INT && y.t == ARR)
    {
        STACK_ELEM z;
        STACK *temp = new_Array(s);
        STACK array = *(STACK *)y.elem;
        int size = array.sp;
        int indice = *(long *)x.elem;
        int buff = size - indice + 1;
        while (buff <= size)
        {
            z = array.stack[buff];
            push(temp, z);
            buff++;
        }
        void *arraypt = malloc(sizeof(STACK));
        *(STACK *)arraypt = *(STACK *)temp;
        z.elem = arraypt;
        z.t = ARR;
        push(s, z);
        free(x.elem);
        free(y.elem);
        return 1;
    }
    else if (x.t == ARR && y.t == INT)
    {
        STACK_ELEM z;
        STACK *temp = new_Array(s);
        STACK array = *(STACK *)x.elem;
        int size = array.sp;
        int indice = *(long *)y.elem;
        int buff = size - indice + 1;
        while (buff <= size)
        {
            z = array.stack[buff];
            push(temp, z);
            buff++;
        }
        void *arraypt = malloc(sizeof(STACK));
        *(STACK *)arraypt = *(STACK *)temp;
        z.elem = arraypt;
        z.t = ARR;
        push(s, z);
        free(x.elem);
        free(y.elem);
        return 1;
    }
    return 0;
}

int removeFirstElem(STACK *s, STACK_ELEM x)
{
    if (x.t == STR)
    {
        int size = strlen(x.elem) + 1;
        char *string = malloc(sizeof(char) * size);
        strcpy(string, x.elem);
        STACK_ELEM caract;
        caract.t = CHAR;
        void *charpt = malloc(sizeof(char));
        *(char *)charpt = string[0];
        caract.elem = charpt;
        string++;
        x.elem = string;
        push(s, x);
        push(s, caract);
        return 1;
    }
    else
    {
        STACK *new_array = new_Array(s);
        STACK_ELEM first;
        STACK_ELEM array;
        int i = 0;
        int maxSp = (*(STACK *)(x.elem)).sp;
        for (i = 1; i <= maxSp; i++)
        {
            if (i == 1)
            {
                first = (*(STACK *)x.elem).stack[i];
            }
            else
            {
                STACK_ELEM other = (*(STACK *)x.elem).stack[i];
                push(new_array, other);
            }
        }
        free(x.elem);
        void *arraySp = malloc(sizeof(STACK));
        *(STACK *)arraySp = *(STACK *)new_array;
        array.t = ARR;
        array.elem = arraySp;
        push(s, array);
        push(s, first);
        return 1;
    }
    return 0;
}

int removeLastElem(STACK *s, STACK_ELEM x)
{
    if (x.t == STR)
    {
        int size = strlen(x.elem) + 1;
        char *string = malloc(sizeof(char) * size);
        strcpy(string, x.elem);
        STACK_ELEM caract;
        caract.t = CHAR;
        void *charpt = malloc(sizeof(char));
        *(char *)charpt = string[size - 2];
        caract.elem = charpt;
        string[size - 2] = '\0';
        x.elem = string;
        push(s, x);
        push(s, caract);
        return 1;
    }
    else if (x.t == ARR)
    {
        STACK_ELEM elem = pop(x.elem); // Usando a função pop remove o elemento do final do array e usando a função push devolve o array sem esse elemento e devolve o elemento.
        push(s, x);
        push(s, elem);
        return 1;
    }
    return 0;
}