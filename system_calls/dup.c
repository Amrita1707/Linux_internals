/*
Name: Amrita N.S
Date: 15-02-2024
Description: WAP to understand usage of dup and dup2 system calls

Pre-requisites:

Knowledge about system calls, How to read and understand ‘man pages’.
Command line arguments, File operation system calls (open, read, write, close ..etc)
Working of dup system calls.
Objective:
To understand and implement using basic system calls.

Requirements:

Using dup or dup2 redirect printf out to a given file instead of printing to stdout.
Pass the file name using command-line arguments.
Try using both system calls (dup and dup2).
Sample Execution:
./dup_dup2 f1.txt
Print this message into file
Print this message into STDOUT

*/

#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	  int opt;
	  printf("select the option\n");
      printf("1:dup\n2:dup2\n");
      scanf("%d",&opt);

      if(opt==1)
	  {
     	//open the file in write mode
	  	int fd = open(argv[1],O_WRONLY);

	  	if(fd == -1)
	  	{
			perror("open");
			return -1;
	  	}
	 
	 	//backup of stdout
	  	int newfd = dup(1);
	  	close(1);

       	//redirect nessage into file.txt
	 	int f = dup(fd);
	  	printf("dup: This statement should be displayed in the file\n");
	 	close(f);
	 
     	//print the msg in stdout
	  	int std = dup(newfd);
	   	printf("dup:This statement should be displayed in the stdout\n");
	  	close(std);	  
	 }
	 else
	 {
         //open the file in write mode
         int fd = open(argv[1],O_WRONLY);
 
         if(fd == -1)
         {
              perror("open");
              return -1;
         }

         //backup of stdout
	   	 int newfd ;
		 dup2(newfd,1);
	 	 close(1);

     	 //redirect nessage into file.txt
	  	 int f = dup2(fd,1);
	  	 printf("dup2: This statement should be displayed in the file\n");
	  	 close(f);
	 
      	 //print the msg in stdout
	  	 int std = dup2(newfd,1);
	  	 printf("dup2:This statement should be displayed in the stdout\n");
	   	 close(std);
		 
	  }
}
