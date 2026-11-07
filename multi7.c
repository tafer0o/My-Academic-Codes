#include <stdio.h>
int main()
{
    int i, n = 7;
    printf("n X i\t7*i\n");
    for (i = 1; i <= 10; i++)
    {
        printf("%d X %d\t= %d\n", n, i, n * i);
    }
    return 0;
}