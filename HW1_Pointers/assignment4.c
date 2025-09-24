#include <stdio.h>

int
main()
{
    int value = 12;
    int* valuePtr = &value;

    int** ptrOfValuePtr = &valuePtr;


    printf("Value by pointer: %d\n", *valuePtr);
    printf("Value by double-pointer: %d\n", **ptrOfValuePtr);
    return 0;
}
