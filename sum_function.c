#include <stdio.h>
int sum(int n1, int n2)
{
    int s;
    s = n1 + n2;
    return s;
}
int main()
// made by Refat Anzum-19
{
    int s = sum(10, 20);
    printf("Sum: %d\n", s);
    return 0;
}