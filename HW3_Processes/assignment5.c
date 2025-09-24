#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    
    if (pid < 0) {
	perror("fork failed.");
	return 1;
    }

    if (pid == 0) {
        printf("Child: PID = %d\n", getpid());
        exit(0);
    } else {
        int status;
        wait(&status);
        printf("Parent: No zombies created.\n");
        sleep(30);
    }

    return 0;
}

