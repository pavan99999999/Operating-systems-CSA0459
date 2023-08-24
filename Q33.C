#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define FRAME_SIZE 3
#define PAGE_SEQUENCE_LENGTH 10

int findOptimal(int pages[], int pageSequenceLength, int frames[], int start) {
    int index = -1;
    int farthest = start;
    
    for (int i = 0; i < FRAME_SIZE; i++) {
        int j;
        for (j = start; j < pageSequenceLength; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    index = i;
                }
                break;
            }
        }
        
        if (j == pageSequenceLength) {
            return i;
        }
    }
    
    return (index == -1) ? 0 : index;
}

void printFrames(int frames[], int n) {
    for (int i = 0; i < n; i++) {
        if (frames[i] == -1) {
            printf(" - ");
        } else {
            printf(" %d ", frames[i]);
        }
    }
    printf("\n");
}

int isPageInFrames(int frames[], int n, int page) {
    for (int i = 0; i < n; i++) {
        if (frames[i] == page) {
            return 1;
        }
    }
    return 0;
}

void simulateOptimal(int pages[], int pageSequenceLength) {
    int frames[FRAME_SIZE];
    int pageFaults = 0;
    int frameIndex = 0;

    for (int i = 0; i < FRAME_SIZE; i++) {
        frames[i] = -1;
    }

    for (int i = 0; i < pageSequenceLength; i++) {
        int currentPage = pages[i];

        if (!isPageInFrames(frames, FRAME_SIZE, currentPage)) {
            if (frameIndex < FRAME_SIZE) {
                frames[frameIndex] = currentPage;
                frameIndex++;
            } else {
                int optimalIndex = findOptimal(pages, pageSequenceLength, frames, i + 1);
                frames[optimalIndex] = currentPage;
            }
            pageFaults++;
        }

        printf("Page %d - Frames:", currentPage);
        printFrames(frames, FRAME_SIZE);
    }

    printf("\nTotal page faults: %d\n", pageFaults);
}

int main() {
    int pageSequence[PAGE_SEQUENCE_LENGTH] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3};
    
    printf("Simulating Optimal Paging:\n");
    simulateOptimal(pageSequence, PAGE_SEQUENCE_LENGTH);

    return 0;
}
