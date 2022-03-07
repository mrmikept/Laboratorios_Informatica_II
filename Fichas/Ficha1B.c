#include <stdio.h>

int main() {
    int x , y ,z, v;
    //x =Raio base maior; y=altura; z=Raio base menor
    if (scanf("%d %d %d", &x, &y, &z) == 3)
    {
    v = ((3.14 * y)/3) * ((x * x) + (x * z) + (z * z));
    printf("%d\n",v);
    }
    return 0;
}