#include <stdio.h>
float area(float n1, float n2)
{
    float a;
    float b = 0.5;
    a = (b * n1 * n2);
    return a;
}
int main()
{
    float a = area(10, 20);
    printf("Area: %.2f\n", a);
    return 0;
}