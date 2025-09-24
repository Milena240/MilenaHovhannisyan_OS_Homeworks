#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int 
main()
{
    pid_t pid = fork();

    if (pid < 0) {
    	perror("fork failed");
	return 1;
    }
    else if (pid == 0) {
        printf("Child PID = %d\n", getpid());
	return 0;
    }
    else {
        printf("Parent PID = %d\n", getpid());
    }

    return 0;
}
