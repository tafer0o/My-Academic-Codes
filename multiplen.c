#include <stdio.h>

int main(void)
{
    int n;

    printf("Enter the value of n: ");
    scanf("%d", &n);

    for (int i = 1; i <= n; i++)
    {
        printf("7 x %d = %d\n", i, 7 * i);
    }

    return 0;
}