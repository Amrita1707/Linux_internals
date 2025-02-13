/*   
close - close a file descriptor

SYNOPSIS
       #include <unistd.h>

       int close(int fd);

DESCRIPTION
       close()  closes a file descriptor, so that it no longer refers to any file and may be reused.  Any record locks (see fcntl(2)) held
       on the file it was associated with, and owned by the process, are removed (regardless of the  file  descriptor  that  was  used  to
       obtain the lock).

       If  fd  is  the last file descriptor referring to the underlying open file description (see open(2)), the resources associated with
       the open file description are freed; if the file descriptor was the  last  reference  to  a  file  which  has  been  removed  using
       unlink(2), the file is deleted.

RETURN VALUE
       close() returns zero on success.  On error, -1 is returned, and errno is set appropriately.

*/


#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	  int fd = open("file1.txt",O_RDONLY);
	  printf("%d\n",fd);
	  if(fd == -1)
	  {
			perror("open");
	  }
	  else
	  {
	 		close(fd);
			printf("%d",fd);
	  }
}

