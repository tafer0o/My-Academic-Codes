#include <stdio.h>
int prime(int n)
{
    for (int i = 2; i < n; i++)
    {
        if (n % i == 0)
        {
            return 0;
        }
    }
    return 1;
} // Made by: Refat Anzum-19
int main()
{
    int m = 0, n = 100;
    for (int i = m; i <= n; i++)
    {
        if (prime(i) == 1)
        {
            printf("%d ", i);
        }
    }
    return 0;
}