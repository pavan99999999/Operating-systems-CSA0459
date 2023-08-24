#include <stdio.h>
#include <stdlib.h>

#define FRAME_SIZE 3
#define PAGE_SEQUENCE_LENGTH 10

typedef struct {
    int page;
    int counter;
} Frame;

int findLRU(Frame frames[], int n) {
    int minCounter = frames[0].counter;
    int lruIndex = 0;

    for (int i = 1; i < n; i++) {
        if (frames[i].counter < minCounter) {
            minCounter = frames[i].counter;
            lruIndex = i;
        }
    }

    return lruIndex;
}

void printFrames(Frame frames[], int n) {
    for (int i = 0; i < n; i++) {
        printf(" %d:%d ", frames[i].page, frames[i].counter);
    }
    printf("\n");
}

int isPageInFrames(Frame frames[], int n, int page) {
    for (int i = 0; i < n; i++) {
        if (frames[i].page == page) {
            return 1;
        }
    }
    return 0;
}

void updateCounters(Frame frames[], int n, int pageIndex) {
    for (int i = 0; i < n; i++) {
        if (frames[i].page != -1) {
            frames[i].counter++;
        }
    }
    frames[pageIndex].counter = 0;
}

void simulateLRU(int pages[], int pageSequenceLength) {
    Frame frames[FRAME_SIZE];
    int pageFaults = 0;

    for (int i = 0; i < FRAME_SIZE; i++) {
        frames[i].page = -1;
        frames[i].counter = 0;
    }

    for (int i = 0; i < pageSequenceLength; i++) {
        int currentPage = pages[i];

        if (!isPageInFrames(frames, FRAME_SIZE, currentPage)) {
            int lruIndex = findLRU(frames, FRAME_SIZE);
            frames[lruIndex].page = currentPage;
            updateCounters(frames, FRAME_SIZE, lruIndex);
            pageFaults++;
        } else {
            for (int j = 0; j < FRAME_SIZE; j++) {
                if (frames[j].page == currentPage) {
                    updateCounters(frames, FRAME_SIZE, j);
                    break;
                }
            }
        }

        printf("Page %d - Frames:", currentPage);
        printFrames(frames, FRAME_SIZE);
    }

    printf("\nTotal page faults: %d\n", pageFaults);
}

int main() {
    int pageSequence[PAGE_SEQUENCE_LENGTH] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3};
    
    printf("Simulating LRU Paging:\n");
    simulateLRU(pageSequence, PAGE_SEQUENCE_LENGTH);

    return 0;
}
