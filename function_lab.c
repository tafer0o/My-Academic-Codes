#include <stdio.h>
int square(int n)
{
    return n * n;
}

int main()
{
    int num = 11;
    printf("Square of %d is %d\n", num, square(num));
    return 0;
}