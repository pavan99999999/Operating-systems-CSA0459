#include <stdio.h>
#include <stdlib.h>
struct Process {
    int id;
    int priority;
};
int findHighestPriority(struct Process processes[], int n) {
    int highestPriorityIndex = 0;
    for (int i = 1; i < n; i++) {
        if (processes[i].priority > processes[highestPriorityIndex].priority) {
            highestPriorityIndex = i;
        }
    }
    return highestPriorityIndex;
}

int main() {
    int numProcesses;

    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);

    struct Process *processes = (struct Process *)malloc(numProcesses * sizeof(struct Process));
    for (int i = 0; i < numProcesses; i++) {
        printf("Enter details for process %d:\n", i + 1);
        processes[i].id = i + 1;
        printf("Enter priority: ");
        scanf("%d", &processes[i].priority);
    }
    int highestPriorityIndex = findHighestPriority(processes, numProcesses);

    printf("Process with highest priority: %d\n", processes[highestPriorityIndex].id);
    free(processes);

    return 0;
}
