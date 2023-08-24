#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 1000

struct Block {
    int size;
    int allocated;
};

void initializeMemory(struct Block *memory, int size) {
    memory->size = size;
    memory->allocated = 0;
}

void worstFit(struct Block *memory, int blockSize) {
    int maxBlockSize = -1;
    int index = -1;

    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (!memory[i].allocated && memory[i].size >= blockSize && memory[i].size > maxBlockSize) {
            maxBlockSize = memory[i].size;
            index = i;
        }
    }

    if (index != -1) {
        memory[index].allocated = 1;
        printf("Allocated memory block of size %d at index %d\n", blockSize, index);
    } else {
        printf("Memory allocation failed for block of size %d\n", blockSize);
    }
}

void deallocateMemory(struct Block *memory, int index) {
    memory[index].allocated = 0;
    printf("Deallocated memory block at index %d\n", index);
}

int main() {
    struct Block memory[MEMORY_SIZE];
    initializeMemory(memory, MEMORY_SIZE);

    worstFit(memory, 200);
    worstFit(memory, 350);
    worstFit(memory, 100);

    // Deallocate the second block
    deallocateMemory(memory, 1);

    worstFit(memory, 300);
    worstFit(memory, 600);

    return 0;
}
