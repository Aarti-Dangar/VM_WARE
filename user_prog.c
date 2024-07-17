#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>

#define SYS_create_thread 462

int main() {
    long res;

    res = syscall(SYS_create_thread);
    if (res < 0) {
       perror("syscall");
        return -1;
    }

    printf("Thread created successfully\n");
    return 0;
}


