#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

const int SIZE = 256;
const int B_SIZE = 4096;

int main() {
    char f1[SIZE], f2[SIZE];
    printf("First file: ");
    scanf("%255s", f1);
    printf("Second file: ");
    scanf("%255s", f2);

    int fd1 = open(f1, O_RDONLY);
    int fd2 = open(f2, O_RDONLY);
    if (fd1 < 0 || fd2 < 0) { 
        perror("open"); 
        exit(1); 
    }

    char b1[B_SIZE], b2[B_SIZE];
    ssize_t n1, n2;
    off_t index = 0;

    while (2) {
        n1 = read(fd1, b1, sizeof(b1));
        n2 = read(fd2, b2, sizeof(b2));

        if (n1 < 0 || n2 < 0) { 
            perror("read"); 
            exit(1);
        }
        ssize_t min = n1 < n2 ? n1 : n2;

        for (ssize_t i = 0; i < min; i++) {
            if (b1[i] != b2[i]) {
                printf("Files differ at byte %ld\n", (long)(index + i));
                close(fd1); 
                close(fd2);
                return 1;
            }
        }
        index += min;

        if (n1 != n2) {
            printf("Files differ at byte %ld (one ended earlier)\n", (long)index);
            close(fd1); 
            close(fd2);
            return 1;
        }
        if (n1 == 0 && n2 == 0) break;
    }

    printf("Files are identical\n");
    close(fd1);
    close(fd2);
    
    return 0;
}

