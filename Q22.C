#include <stdio.h>

#define MEMORY_SIZE 1000 
struct MemoryBlock {
    int id;
    int size;
    int allocated;
};
void bestFit(struct MemoryBlock memory[], int numBlocks, int processId, int processSize) {
    int bestFitIdx = -1; 

    for (int i = 0; i < numBlocks; i++) {
        if (!memory[i].allocated && memory[i].size >= processSize) {
            if (bestFitIdx == -1 || memory[i].size < memory[bestFitIdx].size) {
                bestFitIdx = i;
            }
        }
    }

    if (bestFitIdx != -1) {
        memory[bestFitIdx].allocated = 1;
        memory[bestFitIdx].id = processId;
        printf("Process %d allocated in memory block %d\n", processId, bestFitIdx);
    } else {
        printf("Process %d cannot be allocated due to insufficient memory.\n", processId);
    }
}

int main() {
    struct MemoryBlock memory[10]; 
    int numBlocks = 10; 
    int numProcesses = 5; 
    for (int i = 0; i < numBlocks; i++) {
        memory[i].id = -1;
        memory[i].size = MEMORY_SIZE / numBlocks;
        memory[i].allocated = 0;
    }
    int processes[][2] = {{1, 150}, {2, 300}, {3, 125}, {4, 200}, {5, 175}};
    for (int i = 0; i < numProcesses; i++) {
        bestFit(memory, numBlocks, processes[i][0], processes[i][1]);
    }

    return 0;
}
