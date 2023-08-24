#include <stdio.h>
#include <stdbool.h>
struct Process {
    int id;
    int arrivalTime;
    int burstTime;
};
int findShortestJob(struct Process processes[], bool completed[], int numProcesses) {
    int shortestJobIndex = -1;
    int shortestBurstTime = -1;

    for (int i = 0; i < numProcesses; i++) {
        if (!completed[i] && (shortestJobIndex == -1 || processes[i].burstTime < shortestBurstTime)) {
            shortestJobIndex = i;
            shortestBurstTime = processes[i].burstTime;
        }
    }

    return shortestJobIndex;
}

int main() {
    int numProcesses;

    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);

    struct Process processes[numProcesses];
    bool completed[numProcesses];
    for (int i = 0; i < numProcesses; i++) {
        processes[i].id = i + 1;
        printf("Enter arrival time and burst time for process %d:\n", processes[i].id);
        scanf("%d %d", &processes[i].arrivalTime, &processes[i].burstTime);
        completed[i] = false;
    }

    int currentTime = 0;
    int completedProcesses = 0;

    while (completedProcesses < numProcesses) {
        int shortestJobIndex = findShortestJob(processes, completed, numProcesses);

        if (shortestJobIndex != -1) {
            printf("Executing process %d at time %d\n", processes[shortestJobIndex].id, currentTime);
            currentTime += processes[shortestJobIndex].burstTime;
            completed[shortestJobIndex] = true;
            completedProcesses++;
        } else {
            currentTime++;
        }
    }

    return 0;
}
