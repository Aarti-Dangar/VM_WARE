#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define DEVICE_COUNT 4
#define BUFFER_SIZE 1024

void test_device(const char *device_path, const char *message) {
    int fd;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_written, bytes_read;
    off_t offset;

    // Open device
    fd = open(device_path, O_RDWR);
    if (fd < 0) {
        perror("Failed to open device");
        return;
    }

    // Write to device
    bytes_written = write(fd, message, strlen(message));
    if (bytes_written < 0) {
        perror("Failed to write to device");
        close(fd);
        return;
    }
    printf("Wrote to %s: %s\n", device_path, message);

    // Seek to the beginning of the device
    offset = lseek(fd, 0, SEEK_SET);
    if (offset == (off_t)-1) {
        perror("Failed to seek to the beginning of the device");
        close(fd);
        return;
    }

    // Read from device
    bytes_read = read(fd, buffer, BUFFER_SIZE - 1);
    if (bytes_read < 0) {
        perror("Failed to read from device");
        close(fd);
        return;
    }
    buffer[bytes_read] = '\0';
    printf("Read from %s: %s\n", device_path, buffer);

    // Seek and write to device
    offset = lseek(fd, 5, SEEK_SET);
    if (offset == (off_t)-1) {
        perror("Failed to seek to position 5 in the device");
        close(fd);
        return;
    }
    bytes_written = write(fd, "XYZ", 3);
    if (bytes_written < 0) {
        perror("Failed to write to device at offset 5");
        close(fd);
        return;
    }
    printf("Wrote 'XYZ' to %s at offset 5\n", device_path);

    // Seek to the beginning of the device
    offset = lseek(fd, 0, SEEK_SET);
    if (offset == (off_t)-1) {
        perror("Failed to seek to the beginning of the device");
        close(fd);
        return;
    }

    // Read from device again
    bytes_read = read(fd, buffer, BUFFER_SIZE - 1);
    if (bytes_read < 0) {
        perror("Failed to read from device");
        close(fd);
        return;
    }
    buffer[bytes_read] = '\0';
    printf("Read from %s: %s\n", device_path, buffer);

    // Close device
    close(fd);
}

int main() {
    char device_path[32];
    const char *message = "Hello, Device!";

    for (int i = 0; i < DEVICE_COUNT; i++) {
        snprintf(device_path, sizeof(device_path), "/dev/pseudo_char_device%d", i);
        printf("Testing device: %s\n", device_path);
        test_device(device_path, message);
    }

    return 0;
}

