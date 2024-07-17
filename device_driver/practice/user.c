#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
   int fd;
   char buffer[100];

   fd = open("/dev/lkm_example", O_RDONLY);
   if (fd < 0) {
       perror("Failed to open the device...");
       return -1;
   }
   printf("File successfully opened.\n");
   getchar();
   read(fd, buffer, sizeof(buffer));
   getchar();
   close(fd);

   return 0;
}


