/**
 * @file parse.h
 * @brief Header file que contém a declaração das funções de conversões de tipos usadas em outros modúlos.
 */

char *getToken(char **line);
int parseHandle(STACK *s, char* token);
int tokenType(char *token, int tokenLength);
