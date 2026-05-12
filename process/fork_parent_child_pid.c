#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    // Print a message before fork() is called
    printf("Before fork() \n");
    
    // fork() creates a new process
    // pid will be:
    //   -1 if fork failed
    //    0 in the child process
    //   >0 (child PID) in the parent process
    int pid = fork();

    // Use switch-case to handle the three possible outcomes of fork()
    switch(pid)
    {
        case -1:
            // Error case: fork failed
            perror("fork");
            exit(1);
        case 0:
            // Child process branch
            printf("This is child process. PID - %d \n", getpid());
            sleep(10);
            printf("Child terminated \n");
            exit(0);
        default:
            // Parent process branch
            printf("This is parent process. PID - %d \n", getpid());
            sleep(15);
            printf("Parent terminated \n");
            exit(0);
    }

    return 0;
}
