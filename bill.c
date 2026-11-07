#include <stdio.h>
int main()
{
    float bill, unit;
    printf("The number of units consumed: ");
    scanf("%f", &unit);
    bill = unit * 8.50;
    printf("The total bill is: %.2f Tk", bill);
    return 0;
}