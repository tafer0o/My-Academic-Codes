#include <stdio.h>
int is_even(int n)
{
    if (n % 2 == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int main()
{
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("%d", is_even(n));
    return 0;
}