#include <stdio.h>
int main()
{
    int n;
    printf("Enter the value of n: ");
    scanf("%d", &n);
    if (n > 0)
    {
        printf("Positive");
    }
    else
    {
        printf("Negative");
    }
    return 0;
}