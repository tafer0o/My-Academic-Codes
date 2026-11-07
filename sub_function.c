#include <stdio.h>
int sub(int n1, int n2)
{
    int dif;
    dif = n1 - n2;
    return dif;
}
int main()
{
    int s = sub(20, 10);
    printf("Difference: %d\n", s);
    return 0;
}