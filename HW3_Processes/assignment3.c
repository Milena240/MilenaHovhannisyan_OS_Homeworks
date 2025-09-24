#include <stdio.h>
#include <stdlib.h>

void callBeforeExit1() {
    printf("Function 1 called before exit!\n");
}

void callBeforeExit2() {
    printf("Function 2 called before exit!\n");
}

int main() {
    atexit(callBeforeExit1);
    atexit(callBeforeExit2);

    printf("Program is running...\n");

    exit(0);

    return 0;
}

