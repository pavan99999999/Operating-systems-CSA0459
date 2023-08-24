#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char filename[] = "example.txt";

    // Create a new file for writing
    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error creating file");
        return 1;
    }

    fprintf(file, "Hello, this is a sample text.\n");
    fclose(file);

    printf("File created and written successfully.\n");

    // Append to the existing file
    file = fopen(filename, "a");
    if (file == NULL) {
        perror("Error opening file for appending");
        return 1;
    }

    fprintf(file, "This text is appended to the file.\n");
    fclose(file);

    printf("Text appended to the file.\n");

    // Read from the file
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file for reading");
        return 1;
    }

    printf("File content:\n");
    char buffer[100];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }

    fclose(file);

    return 0;
}
