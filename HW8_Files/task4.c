#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

const int SIZE = 256;
const int BUFFER_SIZE = 512;

int main() {
    int fd = open("log.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0) { 
        perror("open"); 
        exit(1);
    }

    char input[SIZE];
    printf("Enter log line: ");
    ssize_t n = read(0, input, sizeof(input) - 1);
    if (n < 0) { 
        perror("read"); 
        exit(1);
    }
    input[n] = '\0';

    if (input[n-1] == '\n') {
        input[n-1] = '\0';
    }

    char buf[BUFFER_SIZE];
    snprintf(buf, sizeof(buf), "PID=%d: %s\n", getpid(), input);
    ssize_t nr = write(fd, buf, strlen(buf));
    if (nr == -1) perror("write");

    off_t pos = lseek(fd, 0, SEEK_CUR);
    printf("Current offset: %ld\n", (long)pos);

    /// With O_APPEND, every write goes to the file's end, but the kernal still updates the file position (SEEK_CUR)
    /// as if data were written normally, so it keeps increasting
    close(fd);
    return 0;
}

