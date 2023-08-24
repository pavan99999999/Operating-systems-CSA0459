#include <stdio.h>
#include <stdbool.h>
struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int priority;
};
bool allProcessesCompleted(bool completed[], int numProcesses) {
    for (int i = 0; i < numProcesses; i++) {
        if (!completed[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    int numProcesses;

    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);

    struct Process processes[numProcesses];
    bool completed[numProcesses];
    for (int i = 0; i < numProcesses; i++) {
        processes[i].id = i + 1;
        printf("Enter arrival time, burst time, and priority for process %d:\n", processes[i].id);
        scanf("%d %d %d", &processes[i].arrivalTime, &processes[i].burstTime, &processes[i].priority);
        completed[i] = false;
    }

    int currentTime = 0;
    int completedProcesses = 0;

    while (!allProcessesCompleted(completed, numProcesses)) {
        int highestPriority = -1;
        int highestPriorityIndex = -1;

        for (int i = 0; i < numProcesses; i++) {
            if (!completed[i] && processes[i].arrivalTime <= currentTime) {
                if (highestPriority == -1 || processes[i].priority < highestPriority) {
                    highestPriority = processes[i].priority;
                    highestPriorityIndex = i;
                }
            }
        }

        if (highestPriorityIndex != -1) {
            printf("Executing process %d at time %d\n", processes[highestPriorityIndex].id, currentTime);
            processes[highestPriorityIndex].burstTime--;

            if (processes[highestPriorityIndex].burstTime == 0) {
                completed[highestPriorityIndex] = true;
                completedProcesses++;
            }
        }

        currentTime++;
    }

    return 0;
}
