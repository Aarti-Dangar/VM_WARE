#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	char buffer[50];
	int fd1,fd2;
	int length;
	int i=0;

	fd1 = open("/dev/mesg1",O_RDWR);
	if(fd1<0) {
		perror("fd failed");
		exit(2);
	}
	fd2 = open("/dev/mesg2",O_RDWR);
	if(fd2<0) {
		perror("fd failed");
		exit(2);
	}

	printf("write : %d\n", write(fd1, "hello world", sizeof("hello world")));
	
	// set the file position to 0
	lseek(fd2, 0, SEEK_SET);
	perror("lseek");
	memset(buffer, 0, sizeof(buffer));
	length = read(fd2, buffer, sizeof(buffer));
	buffer[length] = '\0';
	printf("Read:%s\tlength:%d\n", buffer, length);
	close(fd1);
	close(fd2);
}
