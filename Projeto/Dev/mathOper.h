/**
 * @file mathOper.h
 * @brief Header file que contém a declaração das funções de operações matemáticas usadas em outros módulos.
 */

int addVal(STACK *s, STACK_ELEM x, STACK_ELEM y);
int sub(STACK *s, STACK_ELEM x, STACK_ELEM y);
int mult(STACK *s, STACK_ELEM x, STACK_ELEM y);
int divd(STACK *s, STACK_ELEM x, STACK_ELEM y);
int dec(STACK *s, STACK_ELEM x);
int inc(STACK *s, STACK_ELEM x);
int modulo(STACK *s, STACK_ELEM x, STACK_ELEM y);
int expo(STACK *s, STACK_ELEM base, STACK_ELEM expon);