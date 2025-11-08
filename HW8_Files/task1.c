#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

const int CHAR_SIZE = 256;
const int BUFFER_SIZE = 4096;

int
main()
{
    char src[CHAR_SIZE], dst[CHAR_SIZE];

    printf("Source file: ");
    scanf("%255s", src);
    printf("Destination file: ");
    scanf("%255s", dst);

    int fd_in = open(src, O_RDONLY);
    if (fd_in < 0) { 
        perror("open source"); 
        exit(1); 
    }

    int fd_out = open(dst, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_out < 0) { 
        perror("open dest"); 
        close(fd_in); 
        exit(1); 
    }

    char buffer[BUFFER_SIZE];
    ssize_t n, total = 0;
    while((n = read(fd_in, buffer, sizeof(buffer))) > 0) {
        ssize_t w = write(fd_out, buffer, n);
	if (w == -1) perror("write");
        if (w != n) {
            perror("write");
            exit(1);
        }
        total += n;
    }
    if (n < 0) perror("read");

    printf("Coped %zd bytes\n", total);
    close(fd_in);
    close(fd_out);
    return 0;

}
