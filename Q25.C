#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

int main() {
    // Demonstrate fcntl system call
    int fd = open("example.txt", O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    int flags = fcntl(fd, F_GETFL);
    if (flags == -1) {
        perror("Error getting file flags");
        close(fd);
        return 1;
    }

    printf("File flags: %d\n", flags);

    close(fd);

    // Demonstrate seek system call
    fd = open("example.txt", O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    off_t offset = lseek(fd, 0, SEEK_END);
    if (offset == -1) {
        perror("Error seeking in file");
        close(fd);
        return 1;
    }

    printf("File size: %lld bytes\n", (long long)offset);

    close(fd);

    // Demonstrate stat system call
    struct stat fileStat;
    if (stat("example.txt", &fileStat) == -1) {
        perror("Error getting file stats");
        return 1;
    }

    printf("File size (stat): %lld bytes\n", (long long)fileStat.st_size);

    // Demonstrate opendir and readdir system calls
    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("Error opening directory");
        return 1;
    }

    printf("Contents of the current directory:\n");
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    closedir(dir);

    return 0;
}
