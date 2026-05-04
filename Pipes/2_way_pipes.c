#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
	int fd[1], fd[2]; 
	pid_t pid;
	char msg[2], buffer[20], reply[20];
	
	printf("enter the string : ");
	scanf("%19[^\n]", msg);
	
	pipe(fd1);
	pipe(fd2);
	
	pid = fork();
	
	if(pid > 0)
	{
		close (fd1[0]); //close read end of fd1
		write(fd1[1], msg, strlen(msg)+1);
		close (fd1[1]); //close write end of fd1
		
		close (fd2[1]); //close write end of fd2
		read(fd2[0], reply, sizeof(reply));
		printf("Parent received message %s : \n", reply);
		close (fd2[0]); //close read end of fd2
	} 
	else
	{
		close (fd1[1]); //close write end of fd1
		read(fd1[0], buffer, sizeof(buffer));
		printf("Child received message %s : \n", buffer);
		close (fd1[0]); //close read end of fd1
		
		close (fd2[0]); //close read end of fd2
		read(fd2[1], reply, sizeof(reply));
		close (fd2[1]); //close write end of fd2
	}
	
	return 0;
}
	
	