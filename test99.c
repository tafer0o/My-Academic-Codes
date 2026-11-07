#include <stdio.h>
int main()
{
    int i, j = 12;
    for (i = 2; i < j; i++)
    {
        if (j % i == 0)
        {
            printf(" Not Prime");
            break;
        }
        else

            if (j % j != 0 && j % i != 0)
        {
            printf(" Not Prime");
        }
        else
        {
            printf("Prime");
        }
    }

    return 0;
}