#include <stdio.h>

int main() {
int i;
for (i=0; (i<20) ; i++)
if (i%2 == 0) putchar ('_');
else putchar ('#');
  return 0;
}