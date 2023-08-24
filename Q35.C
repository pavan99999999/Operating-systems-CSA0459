#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 100
#define BLOCK_SIZE 512

struct IndexBlock {
    int blockPointers[MAX_BLOCKS];
};

struct File {
    int numBlocks;
    struct IndexBlock indexBlock;
};

void initializeFile(struct File *file) {
    file->numBlocks = 0;
    for (int i = 0; i < MAX_BLOCKS; i++) {
        file->indexBlock.blockPointers[i] = -1;
    }
}

void addBlock(struct File *file, int blockNumber) {
    if (file->numBlocks >= MAX_BLOCKS) {
        printf("Maximum number of blocks reached.\n");
        return;
    }

    file->indexBlock.blockPointers[file->numBlocks] = blockNumber;
    file->numBlocks++;
}

void printFile(struct File *file) {
    printf("File content:\n");
    for (int i = 0; i < file->numBlocks; i++) {
        printf("Block %d: Data...\n", file->indexBlock.blockPointers[i]);
    }
}

int main() {
    struct File myFile;
    initializeFile(&myFile);

    int numBlocks;
    printf("Enter the number of blocks for the file: ");
    scanf("%d", &numBlocks);

    for (int i = 0; i < numBlocks; i++) {
        addBlock(&myFile, i);
    }

    printf("File allocation:\n");
    printFile(&myFile);

    return 0;
}
