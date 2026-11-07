#include <stdio.h>
#include <math.h>
int main()
{
    int mark1, mark2, mark3;
    float average, percentage;

    printf("Enter the marks for three subjects: ");
    scanf("%d %d %d", &mark1, &mark2, &mark3);

    printf("Marks entered: %d, %d, %d\n", mark1, mark2, mark3);

    int Total = mark1 + mark2 + mark3;
    average = Total / 3.0;
    percentage = (Total / 300.0) * 100.0;

    printf("Total marks: %d\n", Total);

    printf("The average mark is: %.2f\n", average);

    printf("The percentage is: %.2f%%\n", percentage);
    return 0;
}
