#include <stdio.h>
#include <math.h>

int main() {
    int v1, v2;
    int x=0;
    if ((scanf("%d %d", &v1, &v2)) == 2) {
        while (v1 <= v2)
        {
            int m = (8 * v1) +1;
            if (m % 2 == 0) {
                x++;
            }
            v1++;
        }
    }
    printf("%d\n",x);
    return 0;
}
/*        for (int i=v1; i <= v2; i++)
        {
            int t = checkTriang(i);
            if (t==1) {
                nt++;
            } 
        }
        printf("Triangulares:%d\n",nt);
    }
    return 0;
}

/*int checkTriang(int n) {
    for (int j = 0; j <= n; j++)
    {
        if ((((j+1)*j)/2) == n)
        {
            return 1;
            break;
        }
    }
    return 0;
}*/