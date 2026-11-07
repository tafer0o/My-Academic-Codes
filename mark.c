#include <stdio.h>
int main()
{
    float mark;
    printf("Enter mark: ");
    scanf("%f", &mark);
    if (mark >= 80 && mark <= 100)
    {
        printf("A");
    }
    else if (mark >= 60 && mark <= 79)
    {
        printf("B");
    }
    else if (mark >= 40 && mark <= 59)
    {
        printf("C");
    }
    else if (mark >= 0 && mark <= 39)
    {
        printf("F");
    }
    else
    {
        printf("Invalid mark");
    }
    return 0;
}