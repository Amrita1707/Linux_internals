              /*Implement communication between two related processes using one pipe*/


/*
Requirements: 

Create two child process and execute commands passed from command-line arguments 
Each command is separated by a '|' (pipe) character. 
First child execute first command (with or without options) and pass o/p to next. 
Second child executes second command (after '|') will reads I/p from first cmd. 
Parent will wait for both child process to finish .

Sample execution: 

./pipe (No arguments)
    Error: No arguments passed Usage: ./pipe   <command1 > '|'   <command2>   

2. ./pipe ls  

    Error: Insufficient arguments passed Usage: ./pipe  <command1 > '|'   <command2>   

3. ./pipe ls '|' wc

    5 25 4.
*/	

#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[])
{
	  //check command line line arguments
      if(argc == 1 )
			printf("Error: No arguments passed Usage: ./pipe   <command1 > '|'   <command2>\n"); 

	  //check command line arguments less then 3
	  else if(argc > 1 && argc < 3)
	  {
			printf("Error: Insufficient arguments passed Usage: ./pipe  <command1 > '|'   <command2>\n");
			exit(1);
	  }

	  //check 2nd command is pipe or not
	  else if((strcmp(argv[2],"|"))  == 0)  
	  {	
	  int pfd[2];
	  pipe(pfd);           //create a pipe
	  int ret = fork();    //fork system call to create child process from parent process

	  //child  process
	  if(ret == 0)
	  {
			//write to the pipe
			close(pfd[0]);
			dup2(pfd[1],1);
			execlp(argv[1],argv[1],(char*)NULL);
			exit(0);
	  }

	  //parent process
	  else if(ret > 0)
	  {
			int ret1=fork();  //fork system call to create another child process from parent process

			//child process
			if(ret1 == 0)
			{
				  //read from the pipe
				  close(pfd[1]);
				  dup2(pfd[0],0);
				  execlp(argv[3],argv[3],(char *)NULL);
				  exit(0);
			}

	  }
	  else
	  {
			perror("fork");
			exit(1);
	  }

	  close(pfd[0]);
	  close(pfd[1]);

	  //wait system call to free the resources utilized by the child process
	  wait(NULL);
	  wait(NULL);
	  }
}
