#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
 
#define DEVICE1 "/dev/pseudo_char_device0"
#define DEVICE2 "/dev/pseudo_char_device1"
#define DEVICE3 "/dev/pseudo_char_device2"
#define DEVICE4 "/dev/pseudo_char_device3"
#define BUFFER_SIZE 1024
 
void check_error(int result, const char *operation) {
    if (result < 0) {
        perror(operation);
        exit(EXIT_FAILURE);
    }
}
 
void write_to_device(const char *device, const char *message) {
    int fd = open(device, O_WRONLY);
    check_error(fd, "Open device for writing");
 
    ssize_t bytes_written = write(fd, message, strlen(message));
    check_error(bytes_written, "Write to device");
 
    printf("Written %ld bytes to %s: %s\n", bytes_written, device, message);
 
    close(fd);
}
 
void read_from_device(const char *device) {
    int fd = open(device, O_RDONLY);
    check_error(fd, "Open device for reading");
 
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read = read(fd, buffer, BUFFER_SIZE - 1);
    check_error(bytes_read, "Read from device");
 
    buffer[bytes_read] = '\0'; // Null terminate the buffer
    printf("Read %ld bytes from %s: %s\n", bytes_read, device, buffer);
 
    close(fd);
}
 
int main() {
    const char *message0 = "Hello from device 0!";
    const char *message1 = "Hello from device 1!";
    const char *message2 = "Hello from device 2!";
    const char *message3 = "Hello from device 3!";
    // Write to devices
    write_to_device(DEVICE1, message0);
    write_to_device(DEVICE2, message1);
    write_to_device(DEVICE3, message2);
    write_to_device(DEVICE4, message3);
 
    // Read from devices
    read_from_device(DEVICE1);
    read_from_device(DEVICE2);
    read_from_device(DEVICE3);
    read_from_device(DEVICE4);
 
    return 0;
}
