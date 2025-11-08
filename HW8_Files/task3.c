#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

const int SIZE = 256;

int main() {
    char path[SIZE];
    printf("Enter file path: ");
    scanf("%255s", path);

    int fd = open(path, O_RDONLY);
    if (fd < 0) { 
        perror("open"); 
        exit(1);
    }

    off_t size = lseek(fd, 0, SEEK_END);
    if (size == 0) { 
        ssize_t nr = write(1, "\n", 1);
	if (nr == -1) perror("write");
        close(fd); 
        return 0; 
    }

    char c;
    for (off_t i = size - 1; i >= 0; i--) {
        lseek(fd, i, SEEK_SET);
        if (read(fd, &c, 1) == 1) write(1, &c, 1);
    }

    write(1, "\n", 1);
    close(fd);

    return 0;
}

