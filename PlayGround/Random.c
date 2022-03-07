#include <time.h>
#include <stdlib.h>
#include <stdio.h>

void printRandom();
int main() {
    int menor = 1, maior = 6, count = 1;
    srand(time(0));
    printRandom(menor, maior, count);
    return 0;
}

void printRandom(int menor, int maior, int count) {
    int i;
    for(i=0; i < count; i++) {
        int num = (rand() %
        (maior - menor +1)) + menor;
        printf("%d \n", num);
    }
}