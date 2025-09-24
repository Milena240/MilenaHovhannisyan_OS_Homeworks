#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h>

int
main() 
{

    int ret1 = fork();
    if (ret1 == 0)
        printf("Hello from the first child!\nID: %d Parent ID: %d\n", getpid(), getppid());
    int ret2 = fork();
    if (ret2 == 0)
        printf("Hello from the second child!\nID: %d Parent ID: %d\n", getpid(), getppid());
    int ret3 = fork();
    if (ret3 == 0)
        printf("Hello from the third child!\nID: %d Parent ID: %d\n", getpid(), getppid());
    else
        printf("Hello from the parent!\n");
       
    return 0; 
} 
