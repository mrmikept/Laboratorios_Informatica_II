#include <stdio.h>

int main()
{
    int x, y;
    if (scanf("%d %d", &x, &y) == 2)
    {
        if (x == y)
        {
            printf("IGUAIS\n");
        }
        else
        {
            if (x > y)
            {
                printf("%d\n", x * x);
            }
            else
            {
                printf("%d\n", y * y);
            }
        }
    };
    return 0;
}
