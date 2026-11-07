#include <stdio.h>
int sum(int *a, int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += *(a + i);
    }
    return sum;
}
int main()
{
    int n;
    printf("Enter the size of array: ");
    scanf("%d", &n);

    int a[n];
    printf("Enter the elements of array: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    int and = sum(a, n);
    printf("Sum of array elements: %d", and);
}