#include <stdio.h>
int is_prime(int num)
{
    for (int i = 2; i < num; i++)
    {
        if (num % i == 0)
        {
            return 0;
        }
    }
    if (num <= 1)
    {
        return 0;
    }
    return 1;
}
int main()
{
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    if (is_prime(n) == 1)
    {
        printf("%d is a prime number\n", n);
    }
    else
    {
        printf("%d is not a prime number\n", n);
    }
    return 0;
}