#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    // Creating a new file
    int fileDescriptor = open("example.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if (fileDescriptor == -1) {
        perror("Error creating file");
        return 1;
    }
    
    // Writing to the file
    const char *content = "Hello, this is a demonstration of file operations.\n";
    ssize_t bytesWritten = write(fileDescriptor, content, strlen(content));
    if (bytesWritten == -1) {
        perror("Error writing to file");
        close(fileDescriptor);
        return 1;
    }
    
    printf("File written successfully.\n");
    
    // Closing the file
    close(fileDescriptor);
    
    // Reopening the file for reading
    fileDescriptor = open("example.txt", O_RDONLY);
    if (fileDescriptor == -1) {
        perror("Error opening file for reading");
        return 1;
    }
    
    // Reading and displaying the file's content
    char buffer[1024];
    ssize_t bytesRead;
    printf("File content:\n");
    while ((bytesRead = read(fileDescriptor, buffer, sizeof(buffer))) > 0) {
        write(STDOUT_FILENO, buffer, bytesRead);
    }
    printf("\n");
    
    // Closing the file again
    close(fileDescriptor);
    
    // Removing the file
    if (unlink("example.txt") == -1) {
        perror("Error deleting file");
        return 1;
    }
    
    printf("File deleted successfully.\n");

    return 0;
}
