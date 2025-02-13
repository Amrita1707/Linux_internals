/*
dup, dup2, dup3 - duplicate a file descriptor

int dup(int oldfd);
       
DESCRIPTION
       The  dup()  system  call  creates a copy of the file descriptor oldfd, using the lowest-numbered unused file descriptor for the new
       descriptor.
       After a successful return, the old and new file descriptors may be used interchangeably.  They refer to the same open file descrip‐
       tion  (see open(2)) and thus share file offset and file status flags;

RETURN VALUE
       On success, these system calls return the new file descriptor.  On error, -1 is returned, and errno is set appropriately.

*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	  int fd = open("file.txt",O_WRONLY);

	  // Save the original stdout file descriptor 
	  int std_out = dup(1);

	  // Check if the file was opened successfully  
	  if(fd == -1)
	  {
			perror("open");
			return -1;
	  }

	  // Print a message to the standard output (console)  
	  printf("This will printed in stdout\n");

	  // Close stdout (file descriptor 1)  
	  close(1);

	  // Duplicate fd (file.txt) to stdout, so now all stdout output goes to file.txt 
	  dup(fd);

	  // This message will now be redirected to file.txt instead of the console  
	  printf("This will printed in file\n");

	  // Close the file descriptor for file.txt
	  close(fd);

	  // Close the redirected stdout (fd 1) 
	  close(1);

	  // Restore the original stdout using the saved descriptor  
	  //dup(std_out);
	  return 0;
}

