#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int
main()
{
	pid_t pid1, pid2;
	int status;

	pid1 = fork();
	if (pid1 < 0) {
		perror("fork failed.");
		return 1;
	}
	if (pid1 == 0) {
		printf("First child PID: %d\n", getpid());
		exit(5);
	}

	wait(&status);
	printf("Parent: First child exited with status %d\n", WEXITSTATUS(status));

	pid2 = fork();
	if (pid2 < 0) {
		perror("fork failed.");
		return 0;
	}

	if (pid2 == 0) {
		printf("Second child PID: %d\n", getpid());
		exit(10);
	}


	waitpid(pid2, &status, 0);
	printf("Parent: Second child exitied with status %d\n", WEXITSTATUS(status));

	return 0;

}
