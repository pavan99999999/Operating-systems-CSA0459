#include <stdio.h>

#define FRAME_SIZE 3
#define PAGE_SEQUENCE_LENGTH 10

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

void simulateFIFO(int pages[], int pageSequenceLength) {
    int frames[FRAME_SIZE];
    int frameIndex = 0;
    int pageFaults = 0;

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
                frames[0] = currentPage;
            }
            pageFaults++;
        }

        printf("Page %d - Frames:", currentPage);
        printFrames(frames, FRAME_SIZE);
    }

    printf("\nTotal page faults: %d\n", pageFaults);
}

int main() {
    int pageSequence[PAGE_SEQUENCE_LENGTH] = {1, 2, 3, 4, 5, 6, 1, 2, 7, 8};
    
    printf("Simulating FIFO Paging:\n");
    simulateFIFO(pageSequence, PAGE_SEQUENCE_LENGTH);

    return 0;
}
