#include <stdio.h>
int main()
{
    int j = 1, k = 20;
    for (int i = 0; i <= k; i++)
    {
        i = i + j;
        j++;
        printf("%d ", i);
    }
    return 0;
}