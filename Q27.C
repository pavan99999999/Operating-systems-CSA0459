#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void listDirectory(const char *path) {
    DIR *dir;
    struct dirent *entry;
    struct stat fileStat;

    dir = opendir(path);
    if (dir == NULL) {
        perror("Error opening directory");
        exit(1);
    }

    while ((entry = readdir(dir)) != NULL) {
        char filepath[1024];
        snprintf(filepath, sizeof(filepath), "%s/%s", path, entry->d_name);

        if (stat(filepath, &fileStat) == -1) {
            perror("Error getting file stats");
            closedir(dir);
            exit(1);
        }

        printf("%-20s ", entry->d_name);

        if (S_ISDIR(fileStat.st_mode)) {
            printf("d");
        } else {
            printf("-");
        }

        printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
        printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
        printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
        printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
        printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
        printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
        printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
        printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
        printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");

        printf(" %lld", (long long)fileStat.st_size);
        printf(" %s", ctime(&fileStat.st_mtime));
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        return 1;
    }

    const char *path = argv[1];
    listDirectory(path);

    return 0;
}
