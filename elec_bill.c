#include <stdio.h>
#include <math.h>
int main()
{
    int unit = 100;
    float bill = 0;
    if (unit <= 50)
    {
        bill = unit * 10.5;
    }
    else if (unit <= 70)
    {
        bill = 50 * 10.5;
        bill = bill + (unit - 50) * 12;
    }
    else
    {
        bill = 50 * 10.5;
        bill = bill + 20 * 12;
        bill = bill + (unit - 70) * 15;
    }
    printf("Total bill: %.2f", bill);
    return 0;
}
