#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100

void calculateSeekTime(int requests[], int numRequests, int initialPosition, int maxCylinder) {
    int totalSeekTime = 0;
    int currentHeadPosition = initialPosition;

    // Calculate seek time for moving in one direction
    for (int i = 0; i < numRequests; i++) {
        totalSeekTime += abs(requests[i] - currentHeadPosition);
        currentHeadPosition = requests[i];
    }

    // Calculate seek time for jumping back to the beginning
    totalSeekTime += maxCylinder;

    printf("Total seek time using C-SCAN: %d\n", totalSeekTime);
}

int main() {
    int requests[MAX_REQUESTS];
    int numRequests;
    int initialPosition;
    int maxCylinder;

    printf("Enter the number of requests: ");
    scanf("%d", &numRequests);

    if (numRequests > MAX_REQUESTS) {
        printf("Number of requests exceeds maximum limit.\n");
        return 1;
    }

    printf("Enter the initial head position: ");
    scanf("%d", &initialPosition);

    printf("Enter the maximum cylinder value: ");
    scanf("%d", &maxCylinder);

    printf("Enter the disk request queue:\n");
    for (int i = 0; i < numRequests; i++) {
        scanf("%d", &requests[i]);
    }

    calculateSeekTime(requests, numRequests, initialPosition, maxCylinder);

    return 0;
}
