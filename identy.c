#include <stdio.h>

int main()
{
    float temp[30], max, min, sum = 0, avg;
    int i;

    printf("Enter temperatures for 30 days:\n");

    for (i = 0; i < 30; i++)
    {
        scanf("%f", &temp[i]);
    }

    max = min = temp[0];

    for (i = 0; i < 30; i++)
    {
        if (temp[i] > max)
            max = temp[i];

        if (temp[i] < min)
            min = temp[i];

        sum += temp[i];
    }

    avg = sum / 30;

    printf("Maximum = %.2f\n", max);
    printf("Minimum = %.2f\n", min);
    printf("Average = %.2f\n", avg);

    return 0;
}