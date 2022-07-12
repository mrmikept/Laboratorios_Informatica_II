/**
 * @brief Valor usado para o array de variaveis(26 caracteres usados para váriaveis).
 * 
 */
#define VAR_NUMB 26
/**
 * @file stack.h
 * @brief Header file que contém a declaração das funções de manuseamento da stack usadas em outros modulos e da struck usada para simular a stack.
 */


/**
 * @brief Enum para enumerar os diferentes tipos aceites pela stack.
 * 
 * @param enum CHAR - TYPE para representar chars.
 * @param enum INT - TYPE para representar Inteiros.
 * @param enum DBL - TYPE para representar Doubles.
 * @param enum STR - TYPE para representar Strings
 * @param enum BLK - TYPE para representar Blocos.
 */
typedef enum {
  CHAR,
  INT,
  DBL,
  STR,
  ARR,
  BLK
} TYPE;

/**
 * @struct STACK_ELEM stack.h "stack.h"
 * @brief Estrutura para os elementos da stack.
 * 
 * @param TYPE t - Váriavel para representar qual o tipo do elemento guardado.
 * @param void *elem - Apontador void para o elemento.
 */
typedef struct {
  TYPE t;
  void *elem;
} STACK_ELEM;

/**
 * @struct STACK stack.h "stack.h"  
 * @brief Estrutura STACK, onde simula uma stack usando um array.
 * 
 * @param STACK_ELEM *variables - Array de STACK_ELEM para guardar os valores das váriaveis.
 * @param STACK_ELEM *stack - Array de STACK_ELEM para simular a stack.
 * @param int sp - Apontador para o topo da stack.
 * @param int size - Tamanho máximo atribuido para o array stack.
 */
typedef struct
{
    STACK_ELEM *variables;
    STACK_ELEM *stack;
    int sp;
    int size;
} STACK;


STACK *new_MainStack();
STACK *new_Array(STACK* s);
void push(STACK *s, STACK_ELEM elem);
STACK_ELEM pop(STACK *s);
void printStack(STACK *s);
