#include <stdio.h>
int main()
{
    char s[20] = "Hello World!";
    int length = 0;
    while (s[length] != '\0')
    {
        length++;
    }
    printf("Length of string: %d\n", length);
    return 0;
}