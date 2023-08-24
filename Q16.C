#include <stdio.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

int available[MAX_RESOURCES];
int max[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
int safeSequence[MAX_PROCESSES];
int work[MAX_RESOURCES];
int finish[MAX_PROCESSES];

int checkSafety(int process) {
    for (int i = 0; i < MAX_RESOURCES; i++) {
        if (need[process][i] > work[i])
            return 0;
    }
    return 1;
}

void executeSafetyAlgorithm() {
    int n = MAX_PROCESSES;
    int m = MAX_RESOURCES;
    int numCompleted = 0;
    int safeIndex = 0;

    for (int i = 0; i < m; i++)
        work[i] = available[i];

    while (numCompleted < n) {
        int safeFound = 0;

        for (int i = 0; i < n; i++) {
            if (finish[i] == 0 && checkSafety(i)) {
                safeSequence[safeIndex++] = i;
                finish[i] = 1;

                for (int j = 0; j < m; j++)
                    work[j] += allocation[i][j];

                safeFound = 1;
                numCompleted++;
            }
        }

        if (!safeFound) {
            printf("System is not in a safe state. Deadlock detected.\n");
            return;
        }
    }

    printf("System is in a safe state. Safe sequence: ");
    for (int i = 0; i < n; i++)
        printf("%d ", safeSequence[i]);
    printf("\n");
}

int main() {
    printf("Enter the number of processes: ");
    int numProcesses;
    scanf("%d", &numProcesses);

    printf("Enter the number of resources: ");
    int numResources;
    scanf("%d", &numResources);

    printf("Enter the available resources: ");
    for (int i = 0; i < numResources; i++)
        scanf("%d", &available[i]);

    for (int i = 0; i < numProcesses; i++) {
        printf("Enter the maximum demand of process %d: ", i);
        for (int j = 0; j < numResources; j++)
            scanf("%d", &max[i][j]);
    }

    for (int i = 0; i < numProcesses; i++) {
        printf("Enter the allocation for process %d: ", i);
        for (int j = 0; j < numResources; j++) {
            scanf("%d", &allocation[i][j]);
            need[i][j] = max[i][j] - allocation[i][j];
        }
        finish[i] = 0;
    }

    executeSafetyAlgorithm();

    return 0;
}
