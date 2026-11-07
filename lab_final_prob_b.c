#include <stdio.h>
int main()
{
    int a[4][4], sum = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (a[i][j] % 2 == 0)
            {
                sum = sum + a[i][j];
            }
            else
            {
                printf("  ");
            }
        }
        printf("\n");
    }
    printf("Sum of even elements: %d\n", sum);
    return 0;
}