#include <stdio.h>
int main()
{
    int n = 4;
    printf("i\ti<=5?\t4*i\tprinted\n");
    for (int i = 1; i <= 5; i++)
    {
        printf("%d\t%d\t%d\t%d\n", i, i <= 5, n * i, n * i);
    }
    return 0;
}