#include <stdio.h>

int
main()
{
    int value = 12;
    int* valuePtr = &value;
    
    printf("Address of value by refernece: %p\n", &value);
    printf("Address of value by pointer: %p\n", valuePtr);

    *valuePtr = 16;

    printf("Value after changing it by pointer: %d\n", value);

    return 0;
}
