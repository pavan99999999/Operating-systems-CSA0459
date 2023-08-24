#include <stdio.h>
#include <stdlib.h>

#define MAX_RECORDS 100

struct Record {
    int id;
    char data[50];
};

int main() {
    struct Record records[MAX_RECORDS];
    int numRecords = 0;

    while (1) {
        printf("Enter record data (or 'exit' to finish): ");
        char input[100];
        fgets(input, sizeof(input), stdin);

        if (strcmp(input, "exit\n") == 0) {
            break;
        }

        if (numRecords >= MAX_RECORDS) {
            printf("Maximum number of records reached.\n");
            break;
        }

        records[numRecords].id = numRecords + 1;
        strncpy(records[numRecords].data, input, sizeof(records[numRecords].data) - 1);
        records[numRecords].data[sizeof(records[numRecords].data) - 1] = '\0';
        numRecords++;
    }

    printf("\nRecords in the file:\n");
    for (int i = 0; i < numRecords; i++) {
        printf("Record %d: %s", records[i].id, records[i].data);
    }

    return 0;
}
