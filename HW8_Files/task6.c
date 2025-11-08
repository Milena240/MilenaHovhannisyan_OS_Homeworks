#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    ssize_t nr = 0;
    int fd = open("numbers.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) { 
        perror("open"); 
        exit(1); 
    }

    for (int i = 1; i <= 10; i++) {
        char buf[8];
        int len = snprintf(buf, sizeof(buf), "%d\n", i);
        nr = write(fd, buf, len);
        if (nr == -1) perror("write");
    }
    close(fd);

    fd = open("numbers.txt", O_RDWR);
    if (fd < 0) { 
        perror("open"); 
        exit(1); 
    }

    off_t offset = 0;
    char c;
    int line = 1;
    while (read(fd, &c, 1) == 1 && line < 4) {
        offset++;
        if (c == '\n') line++;
    }

    off_t restPos = lseek(fd, 0, SEEK_CUR);
    off_t end = lseek(fd, 0, SEEK_END);
    size_t restLen = end - restPos;
    char *rest = malloc(restLen);
    lseek(fd, restPos, SEEK_SET);
    read(fd, rest, restLen);

    lseek(fd, offset, SEEK_SET);
    nr = write(fd, "100\n", 4);
    if (nr == -1) perror("write");
    nr = write(fd, rest, restLen);
    if (nr == -1) perror("write");

    free(rest);
    close(fd);

    fd = open("numbers.txt", O_RDONLY);
    char buf[256];
    ssize_t n;
    while ((n = read(fd, buf, sizeof(buf))) > 0) {
        nr = write(1, buf, n);
        if (nr == -1) perror("write");
    }
    close(fd);

    return 0;
}

