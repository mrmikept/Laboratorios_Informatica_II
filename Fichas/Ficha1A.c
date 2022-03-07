#include <stdio.h>

int main() {
    int x , y;
    if (scanf("%d %d", &x, &y) != 2) {
        return 0;
    };
    if (x == y) {
        printf("IGUAIS\n");
    } else { if (x > y)
    {
        x = x * x;
        printf("%d\n",x);
    } else {
        y = y * y;
        printf("%d\n",y);
    }
    }
    return 0;
}