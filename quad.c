#include <stdio.h>
#include <math.h>
int main()
{
    float x1, y1, x2, y2, n;

    printf("Enter coordinates of (x1 y1) and (x2 y2): ");
    scanf("%f %f %f %f", &x1, &y1, &x2, &y2);

    n = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
    float r = sqrt(n);
    printf("Distance: %.2f", r);
    return 0;
}