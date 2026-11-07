#include <stdio.h>
int main()
{
    int n;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter the elements of the array: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    int product = 1;
    for (int i = 0; i < n; i++)
    {
        product = product * arr[i];
    }
    printf("Product of elements in the array: %d", product);
    return 0;
}