#include <stdio.h>

#define MEMORY_SIZE 1000

struct MemoryBlock {
    int start;
    int end;
    int size;
    int isAllocated;
};

void initializeMemory(struct MemoryBlock memory[], int n) {
    for (int i = 0; i < n; i++) {
        memory[i].start = -1;
        memory[i].end = -1;
        memory[i].size = -1;
        memory[i].isAllocated = 0;
    }
}

void allocateMemory(struct MemoryBlock memory[], int n, int processSize) {
    for (int i = 0; i < n; i++) {
        if (!memory[i].isAllocated && memory[i].size >= processSize) {
            memory[i].isAllocated = 1;
            memory[i].size -= processSize;

            printf("Process allocated at memory block %d, remaining size: %d\n", i, memory[i].size);

            if (memory[i].size == 0) {
                memory[i].isAllocated = 0;
                printf("Memory block %d is fully allocated, releasing.\n", i);
            }

            return;
        }
    }

    printf("No suitable memory block found for process of size %d.\n", processSize);
}

int main() {
    int n;
    printf("Enter the number of memory blocks: ");
    scanf("%d", &n);

    struct MemoryBlock memory[n];
    initializeMemory(memory, n);

    for (int i = 0; i < n; i++) {
        printf("Enter size for memory block %d: ", i);
        scanf("%d", &memory[i].size);
        memory[i].start = i * MEMORY_SIZE;
        memory[i].end = memory[i].start + memory[i].size - 1;
    }

    int processSize;
    while (1) {
        printf("Enter process size (-1 to exit): ");
        scanf("%d", &processSize);
        
        if (processSize == -1) {
            break;
        }

        allocateMemory(memory, n, processSize);
    }

    return 0;
}
