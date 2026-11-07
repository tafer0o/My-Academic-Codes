#include <stdio.h>
int main()
{
    for (int i = 1; i <= 20; i++)
    {
        if (i % 7 == 0)
        {
            break;
        }
        printf("%d\n", i);
    }
    return 0;
}