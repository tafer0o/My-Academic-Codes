#include <stdio.h>
#include <string.h>
int main()
{
    char str[50] = "I Am A Student of BAUST ";
    int upper = 0, lower = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] > 'a' &&
            str[i] < 'z')
        {
            lower++;
        } // Made by: Refat Anzum-19
        else if (str[i] > 'A' &&
                 str[i] < 'Z')
        {
            upper++;
        }
    }
    printf("Lowercase letters: %d\n", lower);
    printf("Uppercase letters: %d\n", upper);
}