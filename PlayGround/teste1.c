#include <stdio.h>
#include <math.h> // necessário para raiz

int main()
{
  int x = 0, y = 0, flag = 0, primo = 0;
  scanf("%d %d", &x, &y);
  for (int j = x; j <= y; j++)
  {
    float raiz = sqrt(j);
    if (floorf(raiz) == raiz)
    {
    }
    else
    {
      raiz = floor(raiz);
      for (int i = 2; i <= raiz; i++)
      {
        if (j % i == 0)
        {
          flag = 0;
          break;
        }
        else
        {
          printf("%d é primo!\n", j);
        }
      }
    }
    if (flag == 1)
      primo++;
  }
  // printf("%d\n",primo);
  return 0;
}