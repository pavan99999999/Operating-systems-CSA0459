#include <stdio.h>

struct Process {
    int processID;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int turnaroundTime;
    int isExecuted;
};

int findShortestJob(struct Process processes[], int n, int currentTime) {
    int shortestJobIndex = -1;
    int shortestBurstTime = 999999; // Initialize with a large value
    
    for (int i = 0; i < n; i++) {
        if (processes[i].arrivalTime <= currentTime && processes[i].isExecuted == 0) {
            if (processes[i].burstTime < shortestBurstTime) {
                shortestBurstTime = processes[i].burstTime;
                shortestJobIndex = i;
            }
        }
    }
    
    return shortestJobIndex;
}

void calculateTimes(struct Process processes[], int n) {
    int currentTime = 0;
    int completedProcesses = 0;

    while (completedProcesses < n) {
        int shortestJobIndex = findShortestJob(processes, n, currentTime);

        if (shortestJobIndex == -1) {
            currentTime++;
            continue;
        }

        processes[shortestJobIndex].waitingTime = currentTime - processes[shortestJobIndex].arrivalTime;
        processes[shortestJobIndex].turnaroundTime = processes[shortestJobIndex].waitingTime + processes[shortestJobIndex].burstTime;
        processes[shortestJobIndex].isExecuted = 1;
        currentTime += processes[shortestJobIndex].burstTime;

        completedProcesses++;
    }
}

void displayResults(struct Process processes[], int n) {
    printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].processID, processes[i].arrivalTime,
               processes[i].burstTime, processes[i].waitingTime,
               processes[i].turnaroundTime);
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].processID = i + 1;
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &processes[i].arrivalTime);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burstTime);
        processes[i].isExecuted = 0;
    }

    calculateTimes(processes, n);
    displayResults(processes, n);

    return 0;
}
