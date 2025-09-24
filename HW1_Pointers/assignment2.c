#include <stdio.h>

const int SIZE = 5;

int
main()
{
    int array[SIZE];

    ///filling the array
    for (int count = 0; count < SIZE; ++count) {
        array[count] = count + 1;
    }

    ///traversing and printing each element by pointer
    for (int count = 0; count < SIZE; ++count) {
        printf("%d ", *(array + count));
    }
    printf("\n");

    ///adding each element'c value by 1
    for (int count = 0; count < SIZE; ++count) {
        ++*(array + count);
    }

    ///printing the array by pointer
    for (int count = 0; count < SIZE; ++count) {
        printf("%d ", *(array + count));
    }
    printf("\n");

    ///printing the array by name
    for (int count = 0; count < SIZE; ++count) {
        printf("%d ", array[count]);
    }
    printf("\n");

    return 0;
}
