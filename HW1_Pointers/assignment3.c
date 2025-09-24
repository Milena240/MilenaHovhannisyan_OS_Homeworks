#include <stdio.h>

void swap(int* a, int* b);

int
main()
{
    int a = 5;
    int b = 6;

    printf("Initial value of a: %d\n", a);
    printf("Initial value of b: %d\n", b);


    swap(&a, &b);


    printf("After swap a: %d\n", a); 
    printf("After swap b: %d\n", b);

    return 0;
}

void
swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
