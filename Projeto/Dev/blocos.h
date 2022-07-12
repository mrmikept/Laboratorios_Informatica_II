int createBlock(STACK *s, char **line);
int executeBlock(STACK *s, STACK_ELEM x);
int exeBlockArray(STACK *s, STACK_ELEM a, STACK_ELEM b);
int foldArrayBlock(STACK *s, STACK_ELEM a, STACK_ELEM b);
int exeBlockString(STACK *s, STACK_ELEM str, STACK_ELEM b);
int filterBlock(STACK *s, STACK_ELEM b);
int sortbyBlock(STACK *s, STACK_ELEM b);
