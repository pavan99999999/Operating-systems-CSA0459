#include <stdio.h>
#include <stdbool.h>
struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
};
void roundRobin(struct Process processes[], int numProcesses, int timeQuantum) {
    int currentTime = 0;
    int completedProcesses = 0;

    while (completedProcesses < numProcesses) {
        for (int i = 0; i < numProcesses; i++) {
            if (processes[i].remainingTime > 0) {
                if (processes[i].remainingTime <= timeQuantum) {
                    currentTime += processes[i].remainingTime;
                    processes[i].remainingTime = 0;
                } else {
                    currentTime += timeQuantum;
                    processes[i].remainingTime -= timeQuantum;
                }

                printf("Executing process %d at time %d\n", processes[i].id, currentTime);

                if (processes[i].remainingTime == 0) {
                    completedProcesses++;
                }
            }
        }
    }
}

int main() {
    int numProcesses;
    int timeQuantum;

    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);

    struct Process processes[numProcesses];
    for (int i = 0; i < numProcesses; i++) 
    {
        processes[i].id = i + 1;
        printf("Enter arrival time and burst time for process %d:\n", processes[i].id);
        scanf("%d %d", &processes[i].arrivalTime, &processes[i].burstTime);
        processes[i].remainingTime = processes[i].burstTime;
    }

    printf("Enter time quantum: ");
    scanf("%d", &timeQuantum);
    roundRobin(processes, numProcesses, timeQuantum);

    return 0;
}
