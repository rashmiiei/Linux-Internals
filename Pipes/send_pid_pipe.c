/* 
Create a program where the child process sends its own PID (process ID) to the parent through a pipe, and the parent prints it out.
Output : Parent received child PID : 1995 

*/
#include <stdio.h>
#include <unistd.h>

int main()
{
    int fd[2]; 
    pid_t pid, child_pid;

    pipe(fd); //creating a pipe
    pid = fork(); //creating a child process

    if(pid == 0) //child process
    {
        close(fd[0]); //closing the read end
        child_pid = getpid(); //getting child's pid
        write(fd[1], &child_pid, sizeof(child_pid)); //sending PID
        close(fd[1]); //closing the write end
    }
    else
    {
        close(fd[1]); //closing the write end
        read(fd[0], &child_pid, sizeof(child_pid)); //reading PID
        printf("Parent received child PID : %d \n", child_pid);
        close(fd[0]); //closing the read end
    }

    return 0;

}
