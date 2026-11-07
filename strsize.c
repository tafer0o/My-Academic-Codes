#include <stdio.h>
int main()
{
    int len = 0;
    char name[100];
    gets(name);
    for (int i = 0; name[i] != '\0'; i++)
    {
        len++;
    }
    printf("%d", len);
    return 0;
}