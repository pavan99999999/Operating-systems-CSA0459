#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 100

struct DiskBlock {
    int data;
    int nextBlock;
};

struct File {
    int firstBlock;
    int lastBlock;
};

void initializeDisk(struct DiskBlock *disk, int numBlocks) {
    for (int i = 0; i < numBlocks; i++) {
        disk[i].data = 0;
        disk[i].nextBlock = -1;
    }
}

void addBlock(struct DiskBlock *disk, int blockNumber, int data, int nextBlock) {
    disk[blockNumber].data = data;
    disk[blockNumber].nextBlock = nextBlock;
}

void printFile(struct DiskBlock *disk, struct File *file) {
    int currentBlock = file->firstBlock;
    
    printf("File content:\n");
    while (currentBlock != -1) {
        printf("Block %d: Data = %d\n", currentBlock, disk[currentBlock].data);
        currentBlock = disk[currentBlock].nextBlock;
    }
}

int main() {
    struct DiskBlock disk[MAX_BLOCKS];
    int numBlocks;

    printf("Enter the number of disk blocks: ");
    scanf("%d", &numBlocks);

    initializeDisk(disk, numBlocks);

    struct File myFile;
    myFile.firstBlock = 0;
    myFile.lastBlock = numBlocks - 1;

    for (int i = 0; i < numBlocks; i++) {
        addBlock(disk, i, i * 2, (i + 1) % numBlocks);
    }

    printf("File allocation:\n");
    printFile(disk, &myFile);

    return 0;
}
