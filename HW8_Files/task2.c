#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    ssize_t nr = 0;
    int fd = open("data.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    const char* text = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    nr = write(fd, text, 26);
    if (nr == -1) perror("write");
    close(fd);

    fd = open("data.txt", O_RDWR);
    if (fd < 0) { 
        perror("open"); 
        exit(1);
    }

    off_t size = lseek(fd, 0, SEEK_END);
    printf("Original size: %ld bytes\n", (long)size);

    if (ftruncate(fd, 10) < 0) {
        perror("ftruncate");
        exit(1); 
    }

    size = lseek(fd, 0, SEEK_END);
    printf("New size: %ld bytes\n", (long)size);

    lseek(fd, 0, SEEK_SET);
    char buf[64];
    ssize_t n = read(fd, buf, sizeof(buf) - 1);
    buf[n] = '\0';

    printf("Remaining content: '%s'\n", buf);
    close(fd);
    return 0;

}

