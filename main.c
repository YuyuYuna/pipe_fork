#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

int main(void){
	char write_msg1[BUFFER_SIZE] = "OS TA";
	char write_msg2[BUFFER_SIZE] = "Very handsome";
	char read_msg[BUFFER_SIZE];
	int fd1[2];
	int fd2[2];
	pid_t pid;

	/* create the pipe */ 
	if (pipe(fd1) == -1 || pipe(fd2) == -1) {
		fprintf(stderr,"Pipe failed");
		return 1;
	}

	/* fork a child process */
	pid = fork();
	if(pid < 0) { /* error occurred */ 
		fprintf(stderr, "Fork Failed"); 
		return 1;
	}
	if(pid > 0) { /* parent process */

		close(fd1[READ_END]);
		write(fd1[WRITE_END], write_msg1, strlen(write_msg2)+1);
		close(fd1[WRITE_END]);

		wait(NULL);

		close(fd2[WRITE_END]);
		read(fd2[READ_END], read_msg, BUFFER_SIZE);
		printf("Parent Process read: %s\n\n", read_msg);
		close(fd2[READ_END]);
	}
	else { /* child process */
		

		close(fd1[WRITE_END]);
		read(fd1[READ_END], read_msg, BUFFER_SIZE); 
		printf("\nChild Process read: %s\n",read_msg);
		close(fd1[READ_END]);
		
		close(fd2[READ_END]);
		write(fd2[WRITE_END], write_msg2, strlen(write_msg2)+1);
		close(fd2[WRITE_END]);
	}
	return 0;
}
