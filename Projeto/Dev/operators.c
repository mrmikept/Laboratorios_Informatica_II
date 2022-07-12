/**
 * @file operators.c
 * @brief Ficheiro operators.c que contém as funções de todas as operações.
 *
 */

#include <string.h>
#include "stack.h"
#include "parse.h"
#include "mathOper.h"
#include "BitWOper.h"
#include "StackManOper.h"
#include "Logica.h"
#include "condicoes.h"
#include "arrays.h"
#include "strings.h"
#include "blocos.h"
#include "Debug.h"
#include "variables.h"

/**
 * @brief Função operador ' + '.
 *
 * É comparado o token com a string ' + ', se for igual faz pop dos elementos no topo da stack, verifica o seu tipo e chama a função para executar a respetiva operção de acordo com o tipo dos elementos.
 * Se foi possível executar a operação retorna 1, caso contrario retorna 0.
 * @param[in] STACK *s - Recebe um apontador para a stack.
 * @param char *token - Recebe uma string com o token.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param Function addArrayString(s, x, y) - Função que adiciona um elemento a uma string/array.
 * @param Function addVal(s, x, y) - Função de adição de dois valores do topo da stack.
 */
int plusOperator(STACK *s, char *token)
{
    if (strcmp(token, "+") == 0)
    {
        STACK_ELEM x = pop(s);
        STACK_ELEM y = pop(s);

        if (x.t == ARR || y.t == ARR || x.t == STR || y.t == STR)
        {
            return addArrayString(s, x, y);
        }
        else
        {
            return addVal(s, x, y);
        }
    }
    return 0;
}

/**
 * @brief Função operador ' - '.
 *
 * É comparado o token com a string ' - ', se for igual faz pop dos elementos no topo da stack, verifica o seu tipo e chama a função para executar a respetiva operção de acordo com o tipo dos elementos.
 * Se foi possível executar a operação retorna 1, caso contrario retorna 0.
 * @param[in] STACK *s - Recebe um apontador para a stack.
 * @param char *token - Recebe uma string com o token.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param Function sub(s, x, y) - Função que subtração de dois elementos do topo da stack.
 */
int hyphenOperator(STACK *s, char *token)
{
    if (strcmp(token, "-") == 0)
    {
        STACK_ELEM x = pop(s);
        STACK_ELEM y = pop(s);
        return sub(s, x, y);
    }
    return 0;
}

/**
 * @brief Função operador ' * '.
 *
 * É comparado o token com a string ' * ', se for igual faz pop dos elementos no topo da stack, verifica o seu tipo e chama a função para executar a respetiva operção de acordo com o tipo dos elementos.
 * Se foi possível executar a operação retorna 1, caso contrario retorna 0.
 * @param[in] STACK *s - Recebe um apontador para a stack.
 * @param char *token - Recebe uma string com o token.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param Function foldArrayBlock(s, x, y) - Função que fold um bloco sobre um array.
 * @param Function addarraynvezes(s, x, y) - Função que concatena várias vezes strings ou arrays.
 * @param Function mult(s, x, y) - Função de multiplicação de dois elementos no topo da stack.
 */
int asteriskOperator(STACK *s, char *token)
{
    if (strcmp(token, "*") == 0)
    {
        STACK_ELEM x = pop(s);
        STACK_ELEM y = pop(s);
        if (x.t == BLK)
        {
            return foldArrayBlock(s, y, x);
        }
        else if (y.t == ARR || y.t == STR)
        {
            return addarraynvezes(s, x, y);
        }
        else
        {
            return mult(s, x, y);
        }
    }
    return 0;
}

/**
 * @brief Função operador ' / '.
 *
 * É comparado o token com a string ' / ', se for igual faz pop dos elementos no topo da stack, verifica o seu tipo e chama a função para executar a respetiva operção de acordo com o tipo dos elementos.
 * Se foi possível executar a operação retorna 1, caso contrario retorna 0.
 * @param[in] STACK *s - Recebe um apontador para a stack.
 * @param char *token - Recebe uma string com o token.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param Function subStringSep(s, x, y) - Função que separa uma string por substrings.
 * @param Function divd(s, x, y) - Função de divisão de dois valores do topo da stack.
 */
int fowardSlashOperator(STACK *s, char *token)
{
    if (token[0] == '/' && token[1] == '\0')
    {
        STACK_ELEM y = pop(s);
        STACK_ELEM x = pop(s);
        if (x.t == STR && y.t == STR)
        {
            return subStringSep(s, x, y);
        }
        else
        {
            return divd(s, y, x);
        }
    }
    return 0;
}

/**
 * @brief Função operador ' ( '.
 *
 * É comparado o token com a string ' ( ', se for igual faz pop do elemento no topo da stack, verifica o seu tipo e chama a função para executar a respetiva operção de acordo com o tipo do elemento.
 * Se foi possível executar a operação retorna 1, caso contrario retorna 0.
 * @param[in] STACK *s - Recebe um apontador para a stack.
 * @param char *token - Recebe uma string com o token.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param Function removeFirstElem(s, x) - Função que remove o primeiro elemento de uma string/array e adiciona-o ao topo da stack.
 * @param Function dec(s, x) - Função de decrementação do valor do topo da stack.
 */
int openParentOperator(STACK *s, char *token)
{
    if (strcmp(token, "(") == 0)
    {
        STACK_ELEM x = pop(s);
        if (x.t == ARR || x.t == STR)
        {
            return removeFirstElem(s, x);
        }
        else
        {
            return dec(s, x);
        }
    }
    return 0;
}

/**
 * @brief Função operador ' ) '.
 *
 * É comparado o token com a string ' ) ', se for igual faz pop do elemento no topo da stack, verifica o seu tipo e chama a função para executar a respetiva operção de acordo com o tipo do elemento.
 * Se foi possível executar a operação retorna 1, caso contrario retorna 0.
 * @param[in] STACK *s - Recebe um apontador para a stack.
 * @param char *token - Recebe uma string com o token.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param Function removeLastElem(s, x) - Função que remove o último elemento de uma string/array e adiciona-o ao topo da stack.
 * @param Function addVal(s, x) - Função de incrementação do elemento do topo da stack.
 */
int closeParentOperator(STACK *s, char *token)
{
    if (strcmp(token, ")") == 0)
    {
        STACK_ELEM x = pop(s);
        if (x.t == ARR || x.t == STR)
        {
            return removeLastElem(s, x);
        }
        else
        {
            return inc(s, x);
        }
    }
    return 0;
}

/**
 * @brief Função operador ' % '.
 *
 * É comparado o token com a string ' % ', se for igual faz pop dos elementos no topo da stack, verifica o seu tipo e chama a função para executar a respetiva operção de acordo com o tipo dos elementos.
 * Se foi possível executar a operação retorna 1, caso contrario retorna 0.
 * @param[in] STACK *s - Recebe um apontador para a stack.
 * @param char *token - Recebe uma string com o token.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param Function modulo(s, x, y) - Função de operação modulo de dois valores do topo da stack.
 * @param Function exeBlockArray(s, x, y) - Função que aplica um bloco a um array.
 * @param Function exeBlockString(s, x, y) - Função que aplica um bloco a uma string.
 */
int percentageOperator(STACK *s, char *token)
{
    if (strcmp(token, "%") == 0)
    {
        STACK_ELEM y = pop(s);
        STACK_ELEM x = pop(s);

        if (x.t == INT && y.t == INT)
        {
            return modulo(s, x, y);
        }
        else if (x.t == ARR && y.t == BLK)
        {
            return exeBlockArray(s, x, y);
        }
        else
        {
            return exeBlockString(s, x, y);
        }
    }
    return 0;
}

/**
 * @brief Função operador ' # '.
 *
 * É comparado o token com a string ' # ', se for igual faz pop dos elementos no topo da stack, verifica o seu tipo e chama a função para executar a respetiva operção de acordo com o tipo dos elementos.
 * Se foi possível executar a operação retorna 1, caso contrario retorna 0.
 * @param[in] STACK *s - Recebe um apontador para a stack.
 * @param char *token - Recebe uma string com o token.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param Function substring(s, x, y) - Função que retorna o indice onde aparece uma substring numa string.
 * @param Function expo(s, x, y) - Função de exponenciação de dois valores do topo da stack.
 */
int hashOperator(STACK *s, char *token)
{
    if (strcmp(token, "#") == 0)
    {
        STACK_ELEM y = pop(s);
        STACK_ELEM x = pop(s);
        if (x.t == STR && y.t == STR)
        {
            return substring(s, y, x);
        }
        else
        {
            return expo(s, x, y);
        }
    }
    return 0;
}

/**
 * @brief Função operador ' & '.
 *
 * É comparado o token com a string ' & ', se for igual faz pop dos elementos no topo da stack, verifica o seu tipo e chama a função para executar a respetiva operção de acordo com o tipo dos elementos.
 * Se foi possível executar a operação retorna 1, caso contrario retorna 0.
 * @param[in] STACK *s - Recebe um apontador para a stack.
 * @param char *token - Recebe uma string com o token.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param Function andBitW(s, x, y) - Função e(Bitwise) de dois valores do topo da stack.
 */
int ampersandOperator(STACK *s, char *token)
{
    if (strcmp(token, "&") == 0)
    {
        STACK_ELEM x = pop(s);
        STACK_ELEM y = pop(s);
        return andBitW(s, x, y);
    }
    return 0;
}

/**
 * @brief Função operador ' | '.
 *
 * É comparado o token com a string ' | ', se for igual faz pop dos elementos no topo da stack, verifica o seu tipo e chama a função para executar a respetiva operção de acordo com o tipo dos elementos.
 * Se foi possível executar a operação retorna 1, caso contrario retorna 0.
 * @param[in] STACK *s - Recebe um apontador para a stack.
 * @param char *token - Recebe uma string com o token.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param Function orBitW(s, x, y) - Função ou(BitWise) de dois elementos no topo da stack.
 */
int verticalBarOperator(STACK *s, char *token)
{
    if (strcmp(token, "|") == 0)
    {
        STACK_ELEM x = pop(s);
        STACK_ELEM y = pop(s);
        return orBitW(s, x, y);
    }
    return 0;
}

/**
 * @brief Função operador ' ^ '.
 *
 * É comparado o token com a string ' ^ ', se for igual faz pop dos elementos no topo da stack, verifica o seu tipo e chama a função para executar a respetiva operção de acordo com o tipo dos elementos.
 * Se foi possível executar a operação retorna 1, caso contrario retorna 0.
 * @param[in] STACK *s - Recebe um apontador para a stack.
 * @param char *token - Recebe uma string com o token.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param Function xorBitW(s, x, y) - Função xor(BitWise) de dois elementos no topo da stack.
 */
int circumflexOperator(STACK *s, char *token)
{
    if (strcmp(token, "^") == 0)
    {
        STACK_ELEM x = pop(s);
        STACK_ELEM y = pop(s);
        return xorBitW(s, x, y);
    }
    return 0;
}

/**
 * @brief Função operador ' ~ '.
 *
 * É comparado o token com a string ' ~ ', se for igual faz pop do elemento no topo da stack, verifica o seu tipo e chama a função para executar a respetiva operção de acordo com o tipo do elemento.
 * Se foi possível executar a operação retorna 1, caso contrario retorna 0.
 * @param[in] STACK *s - Recebe um apontador para a stack.
 * @param char *token - Recebe uma string com o token.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param Function notBitW(s, x) - Função not(BitWise) de do elemento do topo da stack.
 * @param Function executeBlock(s, x) - Função que executa um bloco sobre um elemento.
 * @param Function tiraelementos(s, x) - Função que coloca na stack todos os elementos de um array.
 */
int tildeOperator(STACK *s, char *token)
{
    if (strcmp(token, "~") == 0)
    {
        STACK_ELEM x = pop(s);
        if (x.t == INT)
        {
            return notBitW(s, x);
        }
        else if (x.t == BLK)
        {
            return executeBlock(s, x);
        }
        else
        {
            return tiraelementos(s, x);
        }
    }
    return 0;
}

/**
 * @brief Função operador ' _ '.
 *
 * É comparado o token com a string ' _ ', se for igual chama a função para executar a respetiva operação.
 * Se foi possível executar a operação retorna 1, caso contrario retorna 0.
 * @param[in] STACK *s - Recebe um apontador para a stack.
 * @param char *token - Recebe uma string com o token.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param Function duplicate(s, token) - Função que duplica o elemento do topo da stack.
 */
int underscoreOperator(STACK *s, char *token)
{
    if (strcmp(token, "_") == 0)
    {
        return duplicate(s, token);
    }
    return 0;
}

/**
 * @brief Função operador ' ; '.
 *
 * É comparado o token com a string ' ; ', se for igual chama a função para executar a respetiva operação.
 * Se foi possível executar a operação retorna 1, caso contrario retorna 0.
 * @param[in] STACK *s - Recebe um apontador para a stack.
 * @param char *token - Recebe uma string com o token.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param Function inPop(s, token) - Função que faz pop do elemento do topo da stack.
 */
int semicolonOperator(STACK *s, char *token)
{
    if (strcmp(token, ";") == 0)
    {
        return inPop(s, token);
    }
    return 0;
}

/**
 * @brief Função operador ' \ '.
 *
 * É comparado o token com a string ' \ ', se for igual faz pop dos dois elementos no topo da stack e chama a função para executar a respetiva operação.
 * Se foi possível executar a operação retorna 1, caso contrario retorna 0.
 * @param[in] STACK *s - Recebe um apontador para a stack.
 * @param char *token - Recebe uma string com o token.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param Function swapTopTwp(s, token) - Função que troca os dois elementos do topo da stack.
 */
int backslashOperator(STACK *s, char *token)
{
    if (strcmp(token, "\\") == 0)
    {
        STACK_ELEM x = pop(s);
        STACK_ELEM y = pop(s);
        return swapTopTwo(s, x, y);
    }
    return 0;
}

/**
 * @brief Função operador ' @ '.
 *
 * É comparado o token com a string ' @ ', se for igual faz pop dos três elementos no topo da stack e chama a função para executar a respetiva operação.
 * Se foi possível executar a operação retorna 1, caso contrario retorna 0.
 * @param[in] STACK *s - Recebe um apontador para a stack.
 * @param char *token - Recebe uma string com o token.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param Function swapTopThree(s, token) - Função que roda os três elementos do topo da stack.
 */
int atSignOperator(STACK *s, char *token)
{
    if (strcmp(token, "@") == 0)
    {
        STACK_ELEM x = pop(s);
        STACK_ELEM y = pop(s);
        STACK_ELEM z = pop(s);
        return swapTopThree(s, x, y, z);
    }
    return 0;
}

/**
 * @brief Função operador ' $ '.
 *
 * É comparado o token com a string ' \ ', se for igual faz pop do elemento no topo da stack, verifica o seu tipo e chama a função para executar a respetiva operação dependendo do seu tipo.
 * Se foi possível executar a operação retorna 1, caso contrario retorna 0.
 * @param[in] STACK *s - Recebe um apontador para a stack.
 * @param[in] char *token - Recebe uma string com o token.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param Function sortbyBlock(s, n) - Função que ordena um array ou string por um bloco.
 * @param Function copyNEle(s, n) - Função que cópia o n-ésimo elemento de um stack para o topo.
 */
int dollarOperator(STACK *s, char *token)
{
    if (strcmp(token, "$") == 0)
    {
        STACK_ELEM n = pop(s);
        if (n.t == BLK)
        {
            return sortbyBlock(s, n);
        }
        else
        {
            return copyNElem(s, n);
        }
    }
    return 0;
}

/**
 * @brief Função operador ' = ' sobre strings.
 *
 * É verificado o tipo dos elementos recebidos como argumento e chamado a respetiva função para executar a operação dependendo do tipo dos elementos.
 * Se foi possível executar a operação retorna 1, caso contrario retorna 0.
 * @param[in] STACK *s - Recebe um apontador para a stack.
 * @param[in] STACK_ELEM x - Recebe um elemento x.
 * @param[in] STACK_ELEM y - Recebe um elemento y.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param Function igualStr(s, x, y) - Função de operação de igualdade lógica de duas strings.
 * @param Function buscaindstr(s, x, y) - Função que vai buscar um elemento de uma string pelo índice e o põe no topo da stack.
 */
int equalOperatorStr(STACK *s, STACK_ELEM x, STACK_ELEM y)
{
    if ((x.t == STR && y.t == STR))
    {
        return igualStr(s, x, y);
    }
    else
    {
        return buscaindstr(s, x, y);
    }
}

/**
 * @brief Função operador ' = '.
 *
 * É comparado o token com a string ' = ', se for igual faz pop dos elementos no topo da stack, verifica o seu tipo e chama a função para executar a respetiva operção de acordo com o tipo dos elementos.
 * Se foi possível executar a operação retorna 1, caso contrario retorna 0.
 * @param[in] STACK *s - Recebe um apontador para a stack.
 * @param[in] char *token - Recebe uma string com o token.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param Function equalOperatorStr(s, x, y) - Função operador ' = ' sobre strings.
 * @param Function buscaindArr(s, x, y) - Função que vai buscar um elemento de um array pelo índice e o põe no topo da stack.
 * @param Function igualVal(s, x, y) - Função de operação de igualdade lógica de dois valores do topo da stack.
 */
int equalOperator(STACK *s, char *token)
{
    if (strcmp(token, "=") == 0)
    {
        STACK_ELEM y = pop(s);
        STACK_ELEM x = pop(s);
        if (x.t == STR || y.t == STR)
        {
            return equalOperatorStr(s, x, y);
        }
        else if (x.t == ARR || y.t == ARR)
        {
            return buscindArr(s, x, y);
        }
        else
        {
            return igualVal(s, x, y);
        }
    }
    return 0;
}

/**
 * @brief Função operador ' < '.
 *
 * É comparado o token com a string ' < ', se for igual faz pop dos elementos no topo da stack, verifica o seu tipo e chama a função para executar a respetiva operção de acordo com o tipo dos elementos.
 * Se foi possível executar a operação retorna 1, caso contrario retorna 0.
 * @param[in] STACK *s - Recebe um apontador para a stack.
 * @param[in] char *token - Recebe uma string com o token.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param Function buscainicioStr(s, x, y) - Função que vai buscar x elementos do inicio de uma string e o põe no topo da stack.
 * @param Function buscainicioArr(s, x, y) - Função que vai buscar x elementos do inicio de um array e o põe no topo da stack.
 * @param Function menorVal(s, x, y) - Função de operação de menor lógica de dois valores do topo da stack.
 * @param Function menorStr(s, x, y) - Função de operação de menor lógico entre duas strings do topo da stack.
 */
int lessThanOperator(STACK *s, char *token)
{
    if (strcmp(token, "<") == 0)
    {
        STACK_ELEM y = pop(s);
        STACK_ELEM x = pop(s);
        if (x.t == ARR || y.t == ARR)
        {
            return buscinicioArr(s, x, y);
        }
        if (x.t == STR && y.t == STR)
        {
            return menorStr(s, x, y);
        }
        else if (x.t == STR || y.t == STR)
        {
            return buscaindstr(s, x, y);
        }
        else
        {
            return menorVal(s, x, y);
        }
    }
    return 0;
}

/**
 * @brief Função operador ' > '.
 *
 * É comparado o token com a string ' > ', se for igual faz pop dos elementos no topo da stack, verifica o seu tipo e chama a função para executar a respetiva operção de acordo com o tipo dos elementos.
 * Se foi possível executar a operação retorna 1, caso contrario retorna 0.
 * @param[in] STACK *s - Recebe um apontador para a stack.
 * @param[in] char *token - Recebe uma string com o token.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param Function buscaFinalStr(s, x, y) - Função que vai buscar x elementos do inicio de uma string e o põe no topo da stack.
 * @param Function buscaFinalArr(s, x, y) - Função que vai buscar x elementos do inicio de um array e o põe no topo da stack.
 * @param Function maiorVal(s, x, y) - Função de operação de maior lógica de dois valores do topo da stack.
 * @param Function maiorStr(s, x, y) - Função de operação de maior lógico entre duas strings do topo da stack.
 */
int greaterThanOperator(STACK *s, char *token)
{
    if (strcmp(token, ">") == 0)
    {
        STACK_ELEM y = pop(s);
        STACK_ELEM x = pop(s);
        if (x.t == ARR || y.t == ARR)
        {
            return buscaFinalArr(s, x, y);
        }
        if (x.t == STR && y.t == STR)
        {
            return maiorStr(s, x, y);
        }
        else if (x.t == STR || y.t == STR)
        {
            return buscaFinalStr(s, x, y);
        }
        else
        {
            return maiorVal(s, x, y);
        }
    }
    return 0;
}

/**
 * @brief Função operador ' ! '.
 *
 * É comparado o token com a string ' ! ', se for igual faz pop do elemento no topo da stack e chama a função para executar a respetiva operação.
 * Se foi possível executar a operação retorna 1, caso contrario retorna 0.
 * @param[in] STACK *s - Recebe um apontador para a stack.
 * @param char *token - Recebe uma string com o token.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param Function negação(s, x) - Função de operação de negação lógica do elemento do topo da stack.
 */
int exclamationMarkOperator(STACK *s, char *token)
{
    if (strcmp(token, "!") == 0)
    {
        STACK_ELEM x = pop(s);
        return negacao(s, x);
    }
    return 0;
}

/**
 * @brief Função operador ' , '.
 *
 * É comparado o token com a string ' , ', se for igual faz pop do elemento no topo da stack, verifica o seu tipo e chama a função para executar a respetiva operção de acordo com o tipo do elemento.
 * Se foi possível executar a operação retorna 1, caso contrario retorna 0.
 * @param[in] STACK *s - Recebe um apontador para a stack.
 * @param[in] char *token - Recebe uma string com o token.
 * @retval 1 se a função foi executada com sucesso.
 * @retval 0 se não foi possivel executar a função.
 * @param Function filterBlock(s, x) - Função que filtra um array/string por um bloco.
 * @param Function range(s, x) - Função de tamanho/range de um elemento/array/string.
 */
int commaOperator(STACK *s, char *token)
{
    if (strcmp(token, ",") == 0)
    {
        STACK_ELEM x = pop(s);
        if (x.t == BLK)
        {
            return filterBlock(s, x);
        }
        else
        {
            return range(s, x);
        }
    }
    return 0;
}

/**
 * @brief Função Operations Handle que chama as funções dos operadores.
 *
 * @param[in] s Recebe um apontador para a stack.
 * @param[in] token Recebe um token.
 * @param[in] line Recebe um duplo apontador para a string line.
 * @retval 1 se foi executada com êxito.
 * @retval 0 se não foi executada com êxito.
 */
int evenMoreOperationsHandle(STACK *s, char *token)
{
    return (lessThanOperator(s, token) || greaterThanOperator(s, token) || exclamationMarkOperator(s, token) || commaOperator(s, token));
}

/**
 * @brief Função Operations Handle que chama as funções dos operadores.
 *
 * @param[in] s Recebe um apontador para a stack.
 * @param[in] token Recebe um token.
 * @param[in] line Recebe um duplo apontador para a string line.
 * @retval 1 se foi executada com êxito.
 * @retval 0 se não foi executada com êxito.
 */
int moreOperationsHandle(STACK *s, char *token)
{
    return (verticalBarOperator(s, token) || circumflexOperator(s, token) || tildeOperator(s, token) || underscoreOperator(s, token) || semicolonOperator(s, token) || backslashOperator(s, token) || atSignOperator(s, token) || dollarOperator(s, token) || equalOperator(s, token) || evenMoreOperationsHandle(s, token));
}

/**
 * @brief Função Operations Handle que chama as funções dos operadores.
 *
 * @param[in] s Recebe um apontador para a stack.
 * @param[in] token Recebe um token.
 * @param[in] line Recebe um duplo apontador para a string line.
 * @retval 1 se foi executada com êxito.
 * @retval 0 se não foi executada com êxito.
 */
int operationsHandle(STACK *s, char *token)
{
    return (plusOperator(s, token) || hyphenOperator(s, token) || asteriskOperator(s, token) || fowardSlashOperator(s, token) || openParentOperator(s, token) || closeParentOperator(s, token) || percentageOperator(s, token) || hashOperator(s, token) || ampersandOperator(s, token) || moreOperationsHandle(s, token));
}

/**
 * @brief Função Master Handle que chama as restantes funções handle.
 *
 * @param[in] s Recebe um apontador para a stack.
 * @param[in] token Recebe um token.
 * @param[in] line Recebe um duplo apontador para a string line.
 * @retval 1 se foi executada com êxito.
 * @retval 0 se não foi executada com êxito.
 */
int masterHandle(STACK *s, char *token, char **line)
{
    if (token == NULL)
    {
        return 1;
    }
    return (conditionalHandle(s, token) || debugHandle(s, token) || stringsHandle(s, token) || parseHandle(s, token) || createArray(s, token, line) || operationsHandle(s, token) || varHandle(s, token) || stackManipHandle(s, token));
}