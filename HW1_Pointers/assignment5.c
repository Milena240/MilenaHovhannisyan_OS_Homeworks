#include <stdio.h>

int
main()
{
    char str[] = "Hello";
    char* strPtr = str;

    int count = 0;
    while (*strPtr != '\0') {
        printf("%c", *strPtr++);
        ++count;
    }

    printf("\nThe number of characters: %d\n", count);

    return 0;
}
