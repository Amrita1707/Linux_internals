/*
ssize_t read(int fd, void *buf, size_t count); 
Open system call Reads data from a file descriptor into a buffer. 
The number of bytes read is at most the specified count. 
On success, it returns the number of bytes read, zero if EOF is reached, or -1 on error with errno set. 
The file offset is updated accordingly. It may read fewer bytes than requested due to availability. 
Common errors include invalid file descriptor (EBADF), interrupted call (EINTR), and invalid buffer address (EFAULT).
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
int main()
{
	ssize_t ret;
	char buf[20];
	int fd = open("file.txt", O_RDONLY);
    while(read( fd,buf,20))
	{
		printf("%s",buf);
	}
}

