#include <stdio.h>
int main()
{
    int nums[5] = {10, 20, 30, 40, 50};
    int i;
    for (i = 4; i >= 0; i--)
    {
        printf("%d ", nums[i]);
    }
    return 0;
}