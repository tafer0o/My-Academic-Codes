#include <stdio.h>
#include <string.h>
int main()
{
    char s[50] = "I am a student of baust";
    int length = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        if (s[i] == ' ')
        {
            length++;
        }
    }
    printf("Number of words in string: %d\n", length + 1);
    return 0;
}