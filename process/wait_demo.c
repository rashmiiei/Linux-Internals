#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
    printf("Before fork()\n");

    // fork() creates a new process
    // pid will be:
    //   -1 if fork failed
    //    0 in the child process
    int pid = fork();

    // Use switch-case to handle the three possible outcomes of fork()
    switch(pid)
    {
        case -1:
            perror("fork");
            exit(1);
        case 0:
            // Child process branch
            printf("This is child process\n");
            sleep(5);
            exit(0);
        default:
            // Parent process branch
            printf("This is parent process\n");

            // wait(NULL) blocks until *any* child terminates
            // It returns the PID of the terminated child
            printf("Child %d terminated\n", wait(NULL));

            // Parent continues after collecting child's exit status
            sleep(10);
            printf("parent terminated\n");
    }
    return 0;
}
