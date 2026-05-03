/* Write a program where the parent process sends a number to the child process through a pipe, and the child process squares the number and prints the result. 

output : Enter the number you want to send : 21
		 Child : 21 squared = 441
*/

#include <stdio.h>
#include <unistd.h>

int main()
{
    int fd[2];
    pid_t pid;
    int num, result;

    printf("Enter the number you want to send : ");
    scanf("%d", &num);

    pipe(fd); //creating a pipe
    pid = fork(); //creating a child process

    if(pid > 0) //parent process
    {
        close(fd[0]); //closing the read end
        write(fd[1], &num, sizeof(num)); //sending number
        close(fd[1]); //closing write end
    }
    else
    {
        close(fd[1]); //closing write end
        read(fd[0], &num, sizeof(num)); //reading the number
        result = num * num; //squaring the number
        printf("Num is  %d, squared = %d\n", num, result);
        close(fd[0]); //closing the read end
    }

    return 0;
}

