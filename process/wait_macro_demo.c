#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
    printf("Before fork()\n");
    int rpid, status;

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
            rpid = wait(&status);

            if(WIFEXITED(wstatus))
            {
                printf("The child %d terminated normally with the code %d\n", rpid, WEXITSTATUS(wstatus));
            }
            else
            {
                printf("The child %d terminated abnormally \n", rpid);
            }

            
            printf("parent terminated\n");
            exit(0);
    }
    return 0;
}