#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    // Print a message before fork() is called
    printf("before fork() \n");

    // Store the current process ID (this will be the parent's PID)
    int pid = getpid();

    // Create a new process (child). After fork(), both parent and child continue execution.
    fork();

    // Compare the current process ID with the stored parent PID
    if(getpid() == pid)
    {
        // If the PID matches, this is the parent process
        printf("this is parent process \n");
    }
    else
    {
        // Otherwise, this is the child process
        printf("This is child process \n");
    }

    return 0;
}
