#include <stdio.h>
int main()
{
    int a[5] = {1, 2, 3, 4, 3};
    for (int i = 0; i < 5; i++)
    {
        for (int j = i + 1; j < 5; j++)
        {
            if (a[i] == a[j])
            {
                printf("Duplicate found: %d\n", a[i]);
                break;
            }
        }
    }
    return 0;
}