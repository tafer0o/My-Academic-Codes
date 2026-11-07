#include <stdio.h>
int main()
{
    int temp[7] = {32, 25, 18, 35, 20, 15, 30};
    int n;
    for (int i = 0; i < 7; i++)
    {
        if (temp[i] > 30)
        {
            printf("Hot\n");
        }
        else if (temp[i] < 20)
        {
            printf("Cold\n");
        }
        else if (temp[i] <= 30 && temp[i] >= 20)
        {
            printf("Modarate\n");
        }
    }
    return 0;
}