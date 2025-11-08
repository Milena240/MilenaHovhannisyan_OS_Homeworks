#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    ssize_t nr = 0;
    int fd = open("sparse.bin", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) { 
        perror("open"); 
        exit(1); 
    }

    nr = write(fd, "START", 5);
    if (nr == - 1) perror("write");
    lseek(fd, 1024 * 1024, SEEK_CUR);
    nr = write(fd, "END", 3);
    if (nr == - 1) perror("write");
    lseek(fd, 1024 * 1024, SEEK_CUR);
    close(fd);

    fd = open("sparse.bin", O_RDONLY);
    off_t size = lseek(fd, 0, SEEK_END);
    printf("Apparent file size: %ld bytes\n", (long)size);
    close(fd);

    // The actual disk usage is much smaller because the skipped region is lika a hole, unallocated blocks that read as zeros.
    return 0;
}

