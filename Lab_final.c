#include <stdio.h>
int main()
{
    int a[3][3], sum = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }
    printf("Output:\n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (a[i][j] % 2 == 0)
            {
                printf("%d ", a[i][j]);
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