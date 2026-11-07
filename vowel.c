#include <stdio.h>
int main()
{
    char ch = 'J';
    if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' || ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U')
    {
        printf("The character %c is a vowel", ch);
    }
    else
    {
        printf("The character %c is a consonant", ch);
    }
    return 0;
}
