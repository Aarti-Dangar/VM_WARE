#include<stdio.h>
 #include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>

#define MY_DEVICE "/dev/mychardev18"

int main()
{
	int retval;
	char buffer[10];
	pid_t pid;

	printf("opening file:%s\n",MY_DEVICE);
	int fd=open(MY_DEVICE,O_RDONLY);
	if(fd<0)
	{
		perror("open fail");
		return -1;
	}
	fd=open(MY_DEVICE,O_WRONLY);
	if(fd<0)
	{
		perror("open failed\n");
		exit(1);
	}
	getchar();
	retval=write(fd,"hello",sizeof("hello"));
	if(retval<=0)
	{
		perror("open fail");
		return -1;
	}
	getchar();
	printf("written %d bytes\n",retval);
	retval=read(fd,buffer,sizeof(buffer));
	printf("buffer:%s read %d bytes\n",buffer,retval);
	getchar();
        printf("closing file2\n");
        return 0;

}
