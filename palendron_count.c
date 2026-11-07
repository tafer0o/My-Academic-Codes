#include <stdio.h>
#include <string.h>
int main()
{
    char s[20];
    int flag = 1;
    printf("Enter a string: ");
    gets(s);
    for (int i = 0; s[i] != '\0'; i++)
    {
        if (s[i] != s[strlen(s) - i - 1])
        {
            flag = 0;
            break;
        }
    }
    if (flag == 1)
    {
        printf("String is a palindrome\n");
    }
    else
    {
        printf("String is not a palindrome\n");
    }
    return 0;
}