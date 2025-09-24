#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    int pid1 = fork();
    if (pid1 == 0) {
        printf("First child is running...\n");
        execl("/usr/bin/ls", "ls", NULL);
    }

    waitpid(pid1, NULL, 0);
    int pid2 = fork();
    if (pid2 == 0) {
        printf("Second child is running...\n");
        execl("/usr/bin/date", "date", NULL);
    }
    
    waitpid(pid2, NULL, 0);
    printf("Parent process done.\n");
    
    return 0;
}

/*#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    
    if (pid < 0) {
        perror("fork failed");
        return 1;
    }
    else if (pid == 0) {
        // Child process
        execl("/bin/ls", "ls", NULL);
        perror("execl failed");
        _exit(1);
    }
    else { // pid > 0
        // Parent process
        wait(NULL);
        printf("Parent done\n");
    }
    
    return 0;
}*/
