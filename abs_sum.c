#include <stdio.h>
int main()
{
    int a = 2, b = 1;
    int difference = a - b;
    if (difference < 0)
    {
        difference = -difference;
    }
    printf("Absolute difference: %d", difference);
    return 0;
}