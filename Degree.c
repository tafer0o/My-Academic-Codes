#include <stdio.h>
int main()
{
    float c, f;
    printf("Enter the value of fahrenheit: ");
    scanf("%f", &f);
    c = (f - 32) * 5 / 9;
    printf("The value in celsius is: %f", c);
    return 0;
}