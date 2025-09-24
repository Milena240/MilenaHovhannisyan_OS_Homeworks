#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2;
    int status;

    pid1 = fork();
    if (pid1 < 0) {
	perror("fork failed.");
	return 1;
    }
    if (pid1 == 0) {
        exit(42); 
    }

    pid2 = fork();
    if (pid2 < 0) {
	perror("fork failed.");
	return 1;
    }
    if (pid2 == 0) {
        exit(84); 
    }

    waitpid(pid1, &status, 0);
    if (WIFEXITED(status))
        printf("Child 1 exited normally with status %d\n", WEXITSTATUS(status));
    else
        printf("Child 1 exited abnormally\n");

    waitpid(pid2, &status, 0);
    if (WIFEXITED(status))
        printf("Child 2 exited normally with status %d\n", WEXITSTATUS(status));
    else
        printf("Child 2 exited abnormally\n");

    return 0;
}

