#include <stdio.h>
int main()
{
    char ch;
    printf("Enter a character: ");
    scanf("%c", &ch);
    if (ch >= 'a' && ch <= 'z')
    {
        printf("The character %c is lowercase alphabet", ch);
    }
    else if (ch >= 'A' && ch <= 'Z')
    {
        printf("The character %c is uppercase alphabet", ch);
    }
    else
    {
        printf("The character %c is not alphabet", ch);
    }
}
