/* Program where a two way communicaton happens between a parent and a child

output : enter the string : hi child
		 Child received message : hi child 
		 Parent received message : Hi parent
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
	int fd1[2], fd2[2]; // fd1: parent → child, fd2: child → parent
	pid_t pid;
	char msg[2], buffer[20], reply[20];

	// Parent takes input string
	printf("enter the string : ");
	scanf("%19[^\n]", msg);

	// Create two pipes
	pipe(fd1);
	pipe(fd2);
	
	pid = fork(); // Create child process
	
	if(pid > 0) // Parent process
	{
		//Parent sends message to child
		close (fd1[0]); //close read end of fd1
		write(fd1[1], msg, strlen(msg)+1);
		close (fd1[1]); //close write end of fd1

		//Parent waits for reply from child
		close (fd2[1]); //close write end of fd2
		read(fd2[0], reply, sizeof(reply));
		printf("Parent received message : %s \n", reply);
		close (fd2[0]); //close read end of fd2
	} 
	else // Child process
	{
		//Child reads message from parent
		close (fd1[1]); //close write end of fd1
		read(fd1[0], buffer, sizeof(buffer));
		printf("Child received message %s : \n", buffer);
		close (fd1[0]); //close read end of fd1

		//Child sends reply back to parent
		close (fd2[0]); //close read end of fd2
        char response[] = "Hi parent";
		write(fd2[1], response, strlen(response)+1);
		close (fd2[1]); //close write end of fd2
	}
	
	return 0;
}
	
	
