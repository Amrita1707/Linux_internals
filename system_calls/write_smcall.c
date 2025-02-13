/*
write - write to a file descriptor

SYNOPSIS
       #include <unistd.h>

       ssize_t write(int fd, const void *buf, size_t count);

DESCRIPTION
       write() writes up to count bytes from the buffer starting at buf to the file referred to by the file descriptor fd.

       The  number of bytes written may be less than count if, for example, there is insufficient space on the underlying physical medium,
       or the RLIMIT_FSIZE resource limit is encountered (see setrlimit(2)), or the call was interrupted by a signal handler after  having
       written less than count bytes.  (See also pipe(7).)

RETURN VALUE
       On success, the number of bytes written is returned (zero indicates nothing was written).  It is not an error  if  this  number  is
       smaller than the number of bytes requested; this may happen for example because the disk device was filled.
       On error, -1 is returned, and errno is set appropriately.
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	  char buf[100] = "write system call is for write to a file descriptor\n";
	  int i =0,len=0;
	  for(i=0; buf[i] != '\0'; i++)
	  {
			len++;
	  }
	  int fd = open("file.txt", O_WRONLY);
	  if(fd == -1)
			printf("Error opening the file");
	  else
			write(fd, buf, len);

}

