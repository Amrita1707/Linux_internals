/*
Name : Amrita
Date : 13-02-2025
Description : WAP to understand usage of dup and dup2 system calls

Using dup or dup2 redirect printf out to a given file instead of printing to stdout.
Pass the file name using command-line arguments.
Try using both system calls (dup and dup2).

The  dup()  system  call  creates a copy of the file descriptor oldfd, using the lowest-numbered unused file descriptor for the new
descriptor.
After a successful return, the old and new file descriptors may be used interchangeably.  They refer to the same open file descrip‐
tion  (see open(2)) and thus share file offset and file status flags.
dup2() The  dup2()  system  call performs the same task as dup(), but instead of using the lowest-numbered unused file descriptor, it uses
the file descriptor number specified in newfd.  If the file descriptor newfd was previously open,  it  is  silently  closed  before being reused.

*/

#include<stdio.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

int main( int argc, char *argv[])
{
      int opt;
	  printf("select the option\n");
	  printf("1:dup\n2:dup2\n");
	  scanf("%d",&opt);

	  if( argc < 2)
	  {
			printf("Invalid argument\n");
			return -1;
	  }
	  //dup
	  if(opt==1)
	  {
		//open the file in write mode
        int fd = open(argv[1], O_WRONLY);
	  	if(fd == -1)
	  	{
			perror("open");
			return -1;
	  	}

		 //backup of stdout
		 int std_cpy = dup(1);
	     close(1);

         //redirect nessage into file.txt 
	   	 int new_fd = dup(fd);
	  	 printf("dup: This statement should be displayed in the file\n");
	  	 close(new_fd);

         //print the msg in stdout
		 int std = dup(std_cpy);
		 printf("dup: This statement should be displayed in the stdout\n"); 
		 close(std);
	  }
	  else
	  {
          
         //open the file in write mode
	 	 int fd = open(argv[1], O_WRONLY);
	  	 if(fd == -1)
	  	 {
			perror("open");
			return -1;
	  	 }
		
	     int std_cpy;
		 dup2(std_cpy,1);
         close(1);

         //redirect nessage into file.txt 
         int new_fd = dup2(fd,1);
         printf("dup2: This statement should be displayed in the file\n");
         close(new_fd);

         //print the msg in stdout
         int std = dup2(std_cpy,1);
		 printf("dup2 : THis statement should be displayed in the stdout\n");
		 close(std);

	 } 
}

