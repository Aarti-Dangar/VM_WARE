#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd;
    char buffer[100];
    ssize_t bytes_read;

    fd = open("/dev/lkm_example", O_RDONLY);
    if (fd < 0) {
        perror("Failed to open the device...");
        return -1;
    }
    printf("File successfully opened.\n");

    bytes_read = read(fd, buffer, sizeof(buffer) - 1);
    if (bytes_read < 0) {
        perror("Failed to read the device...");
        close(fd);
        return -1;
    }

    buffer[bytes_read] = '\0'; // Null-terminate the buffer
    printf("Read from device: %s\n", buffer);

    close(fd);
    return 0;
}

