#include <stdio.h>
int main()
{
    float M;

    printf("Enter value in Mile: ");
    scanf("%f", &M);

    float km = M * 1.62;

    printf("Value in Kilometer: %.2f", km);

    return 0;
}
