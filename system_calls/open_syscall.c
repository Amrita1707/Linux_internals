#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
int main()
{
	  // File descriptor variable
	  int fd;
	  // Attempt to open "file.txt" in read-only mode, creating it if it does not exist.
      // The O_EXCL flag ensures that the file is created only if it does not already exist.
	  fd = open("file.txt",O_RDONLY | O_CREAT | O_EXCL, 0666);
	  if(fd == -1)
			printf("open failed\n");
	  else
	  		printf("file.txt is opened in read mode\n");
	
	  // Check for specific error types using errno
	  // Permission denied error
	  if(errno == EACCES)
			printf("Access denied\n");
	  // File not found error
	  else if(errno == ENOENT)
			printf("File not found\n");
	  // File already exists error
	  else if( errno == EEXIST)
			printf("file already exist\n");
}

