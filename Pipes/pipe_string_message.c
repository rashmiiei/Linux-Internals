/* Write a C program where the parent sends a string to the child using a pipe, and the child prints it. */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
int main()
{
	int fd[2];
	pid_t pid;
	char msg[20];

    printf("enter the sring : ");
    scanf("%19[^\n]", msg);
	char buffer[20];
	
	pipe(fd);
	pid = fork();
	
	if(pid > 0) //parent process
	{
		close (fd[0]); //close read end
		write(fd[1], msg, strlen(msg)+1);
		close (fd[1]); //close write end
	}
	else
	{
		close (fd[1]); //close write end
		read(fd[0], buffer, sizeof(buffer));
		printf("Child received the message : %s \n", buffer);
		close (fd[0]); //close read end
	}
	
	return 0;
}


		
