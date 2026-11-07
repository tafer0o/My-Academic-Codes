#include <stdio.h>
int main()

{
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    if (n % 2 == 0 && n % 7 == 0)
    {
        printf("The number %d is divisible by both 2 & 7", n);
    }
    else
    {
        printf("The number %d is not divisible by both 2 & 7", n);
    }
    return 0;
}
