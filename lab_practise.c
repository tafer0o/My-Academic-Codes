#include <stdio.h>
int main()
{
    int a;
    float f;
    char c;
    printf("Enter an value: ");
    scanf("%d", &a);

    printf("Enter a float: ");
    scanf("%f", &f);

    printf("Enter a character: ");
    scanf(" %c", &c);
    printf("int=%d, float=%f, char=%c", a, f, c);
    return 0;
}
