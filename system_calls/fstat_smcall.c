/*

int fstat(int fd, struct stat *statbuf);

DESCRIPTION
These  functions  return  information  about  a file, in the buffer pointed to by statbuf.  No permissions are required on the file
itself, but—in the case of stat(), fstatat(), and lstat()—execute (search) permission is required on  all  of  the  directories  in
pathname that lead to the file.

stat() and fstatat() retrieve information about the file pointed to by pathname; the differences for fstatat() are described below.
lstat()  is identical to stat(), except that if pathname is a symbolic link, then it returns information about the link itself, not
the file that it refers to.
fstat() is identical to stat(), except that the file about which information is to be retrieved is specified by the file descriptor
fd.

RETURN VALUE
On success, zero is returned.  On error, -1 is returned, and errno is set appropriately.

*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h> 
#include <fcntl.h>

int main()
{
	  int fd = open("file.txt", O_RDONLY);
	  // Check if the file was opened successfully
	  if( fd == -1)
	  {
			perror("open");
			return -1;
	  }
	  struct stat buf;
	  
	  // Get file statistics using fstat()  
	  if( fstat(fd,&buf) == -1)
	  {
			perror("fstat");
			return -1;
	  }
	  // Print file details: inode number, size, mode, and user ID of the owner 
	  printf("Inode number-%ld\nsize-%ld\nmode-%d\nUser ID of owner-%d",buf.st_ino,buf.st_size,buf.st_mode,buf.st_uid);
}

