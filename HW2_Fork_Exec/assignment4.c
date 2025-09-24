#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main()
{
    int pid = fork();
    if (pid == 0) {
        printf("Child is running...\n");
        execl("/usr/bin/grep", "echo", "Milena", "./test.txt", NULL);
    }
    else {
        wait(NULL);
        printf("Parent process done.\n");
    }
    return 0;
}
