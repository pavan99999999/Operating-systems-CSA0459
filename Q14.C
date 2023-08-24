#include <stdio.h>
#include <string.h>

#define MAX_DIRS 10
#define MAX_FILES_PER_DIR 10
#define DIR_NAME_LENGTH 20
#define FILE_NAME_LENGTH 20

struct File {
    char name[FILE_NAME_LENGTH];
    int size;
};

struct Directory {
    char name[DIR_NAME_LENGTH];
    struct File files[MAX_FILES_PER_DIR];
    int fileCount;
};

struct RootDirectory {
    struct Directory directories[MAX_DIRS];
    int dirCount;
};

void initializeRootDirectory(struct RootDirectory *rootDir) {
    rootDir->dirCount = 0;
}

void createDirectory(struct RootDirectory *rootDir, const char *dirName) {
    if (rootDir->dirCount < MAX_DIRS) {
        strcpy(rootDir->directories[rootDir->dirCount].name, dirName);
        rootDir->directories[rootDir->dirCount].fileCount = 0;
        rootDir->dirCount++;
        printf("Directory '%s' created\n", dirName);
    } else {
        printf("Root directory is full, cannot create more directories.\n");
    }
}

struct Directory *findDirectory(struct RootDirectory *rootDir, const char *dirName) {
    for (int i = 0; i < rootDir->dirCount; i++) {
        if (strcmp(rootDir->directories[i].name, dirName) == 0) {
            return &rootDir->directories[i];
        }
    }
    return NULL;
}

void createFile(struct Directory *dir, const char *name, int size) {
    if (dir->fileCount < MAX_FILES_PER_DIR) {
        strcpy(dir->files[dir->fileCount].name, name);
        dir->files[dir->fileCount].size = size;
        dir->fileCount++;
        printf("File '%s' created with size %d in directory '%s'\n", name, size, dir->name);
    } else {
        printf("Directory '%s' is full, cannot create more files.\n", dir->name);
    }
}

void listFiles(const struct Directory *dir) {
    printf("Files in directory '%s':\n", dir->name);
    for (int i = 0; i < dir->fileCount; i++) {
        printf("File: %s, Size: %d\n", dir->files[i].name, dir->files[i].size);
    }
}

int main() {
    struct RootDirectory myRootDirectory;
    initializeRootDirectory(&myRootDirectory);

    createDirectory(&myRootDirectory, "documents");
    struct Directory *docsDirectory = findDirectory(&myRootDirectory, "documents");

    if (docsDirectory != NULL) {
        createFile(docsDirectory, "report.txt", 1024);
        createFile(docsDirectory, "notes.txt", 512);
        listFiles(docsDirectory);
    } else {
        printf("Directory not found\n");
    }

    return 0;
}
