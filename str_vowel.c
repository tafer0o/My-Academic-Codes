#include <stdio.h>
#include <string.h>
int main()
{
    char s[50] = "i am a student of baust";
    int length = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u')
        {
            length++;
        }
    }
    printf("Number of vowels in string: %d\n", length);
    return 0;
}