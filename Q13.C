#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 100

// Node structure for memory blocks
typedef struct Node {
    int start;
    int size;
    struct Node *next;
} Node;

Node *freeList = NULL;

// Initialize the free list with the entire memory
void initializeMemory() {
    freeList = (Node *)malloc(sizeof(Node));
    freeList->start = 0;
    freeList->size = MEMORY_SIZE;
    freeList->next = NULL;
}

// Allocate memory using First Fit strategy
void firstFit(int processSize) {
    Node *current = freeList;
    Node *prev = NULL;

    while (current != NULL) {
        if (current->size >= processSize) {
            Node *allocatedBlock = (Node *)malloc(sizeof(Node));
            allocatedBlock->start = current->start;
            allocatedBlock->size = processSize;
            allocatedBlock->next = NULL;

            if (prev == NULL) {
                freeList = current->next;
            } else {
                prev->next = current->next;
            }

            current->start += processSize;
            current->size -= processSize;

            printf("Allocated %d units at memory starting from %d (First Fit)\n", processSize, allocatedBlock->start);
            return;
        }

        prev = current;
        current = current->next;
    }

    printf("Not enough memory for %d units using First Fit\n", processSize);
}

// Allocate memory using Best Fit strategy
void bestFit(int processSize) {
    Node *current = freeList;
    Node *bestFitBlock = NULL;
    int minFragmentation = MEMORY_SIZE;

    while (current != NULL) {
        if (current->size >= processSize && current->size - processSize < minFragmentation) {
            bestFitBlock = current;
            minFragmentation = current->size - processSize;
        }
        current = current->next;
    }

    if (bestFitBlock != NULL) {
        Node *allocatedBlock = (Node *)malloc(sizeof(Node));
        allocatedBlock->start = bestFitBlock->start;
        allocatedBlock->size = processSize;
        allocatedBlock->next = NULL;

        bestFitBlock->start += processSize;
        bestFitBlock->size -= processSize;

        printf("Allocated %d units at memory starting from %d (Best Fit)\n", processSize, allocatedBlock->start);
    } else {
        printf("Not enough memory for %d units using Best Fit\n", processSize);
    }
}

// Allocate memory using Worst Fit strategy
void worstFit(int processSize) {
    Node *current = freeList;
    Node *worstFitBlock = NULL;
    int maxFragmentation = 0;

    while (current != NULL) {
        if (current->size >= processSize && current->size - processSize > maxFragmentation) {
            worstFitBlock = current;
            maxFragmentation = current->size - processSize;
        }
        current = current->next;
    }

    if (worstFitBlock != NULL) {
        Node *allocatedBlock = (Node *)malloc(sizeof(Node));
        allocatedBlock->start = worstFitBlock->start;
        allocatedBlock->size = processSize;
        allocatedBlock->next = NULL;

        worstFitBlock->start += processSize;
        worstFitBlock->size -= processSize;

        printf("Allocated %d units at memory starting from %d (Worst Fit)\n", processSize, allocatedBlock->start);
    } else {
        printf("Not enough memory for %d units using Worst Fit\n", processSize);
    }
}

int main() {
    initializeMemory();

    int choice, processSize;

    while (1) {
        printf("\n1. First Fit Allocation\n");
        printf("2. Best Fit Allocation\n");
        printf("3. Worst Fit Allocation\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 4) {
            break;
        }

        printf("Enter process size: ");
        scanf("%d", &processSize);

        switch (choice) {
            case 1:
                firstFit(processSize);
                break;
            case 2:
                bestFit(processSize);
                break;
            case 3:
                worstFit(processSize);
                break;
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
