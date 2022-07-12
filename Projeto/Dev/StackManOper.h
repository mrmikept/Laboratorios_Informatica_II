/**
 * @file StackManOper.h
 * @brief Header file que contém a declaração das funções de operações de manipulação da stack usadas em outros módulos.
 */

int swapTopTwo(STACK *s, STACK_ELEM x, STACK_ELEM y);
int swapTopThree(STACK *s, STACK_ELEM x, STACK_ELEM y, STACK_ELEM z);
int copyNElem(STACK *s, STACK_ELEM n);
int inPop(STACK *s, char *token);
int duplicate(STACK *s, char *token);
int stackManipHandle(STACK *s, char *token);