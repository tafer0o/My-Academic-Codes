#include <stdio.h>
int main()
{
    char name[100];
    gets(name);
    printf("Hello, ");
    puts(name);
    printf("length=%d\n", strlen(name));
    return 0;
}
