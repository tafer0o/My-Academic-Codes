#include <stdio.h>
int main()
{
    int a[10] = {5, 11, 17, 12, 22, 24, 26, 60, 32, 62};
    printf("Even: ");
    for (int i = 0; i < 10; i++)
    {
        if (a[i] % 2 == 0)
        {
            printf("%d ", a[i]);
        }
    }
    printf("\nOdd: ");
    for (int i = 0; i < 10; i++)
    {
        if (a[i] % 2 != 0)
        {
            printf("%d ", a[i]);
        }
    }
    return 0;
}