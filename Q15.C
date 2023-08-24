#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_RECORDS 100

struct Employee {
    int id;
    char name[MAX_NAME_LENGTH];
    float salary;
};

void displayMenu() {
    printf("\nEmployee Record System\n");
    printf("1. Add Employee\n");
    printf("2. Modify Employee\n");
    printf("3. Delete Employee\n");
    printf("4. View Employee Details\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}

void addEmployee(FILE *file) {
    struct Employee emp;
    printf("Enter employee ID: ");
    scanf("%d", &emp.id);
    printf("Enter employee name: ");
    scanf("%s", emp.name);
    printf("Enter employee salary: ");
    scanf("%f", &emp.salary);

    fseek(file, (emp.id - 1) * sizeof(struct Employee), SEEK_SET);
    fwrite(&emp, sizeof(struct Employee), 1, file);
    printf("Employee added successfully!\n");
}

void modifyEmployee(FILE *file) {
    int id;
    printf("Enter employee ID to modify: ");
    scanf("%d", &id);

    struct Employee emp;
    fseek(file, (id - 1) * sizeof(struct Employee), SEEK_SET);
    fread(&emp, sizeof(struct Employee), 1, file);

    if (emp.id == 0) {
        printf("Employee not found\n");
        return;
    }

    printf("Enter new employee name: ");
    scanf("%s", emp.name);
    printf("Enter new employee salary: ");
    scanf("%f", &emp.salary);

    fseek(file, (emp.id - 1) * sizeof(struct Employee), SEEK_SET);
    fwrite(&emp, sizeof(struct Employee), 1, file);
    printf("Employee modified successfully!\n");
}

void deleteEmployee(FILE *file) {
    int id;
    printf("Enter employee ID to delete: ");
    scanf("%d", &id);

    struct Employee emp;
    emp.id = 0;
    fseek(file, (id - 1) * sizeof(struct Employee), SEEK_SET);
    fwrite(&emp, sizeof(struct Employee), 1, file);
    printf("Employee deleted successfully!\n");
}

void viewEmployeeDetails(FILE *file) {
    int id;
    printf("Enter employee ID to view details: ");
    scanf("%d", &id);

    struct Employee emp;
    fseek(file, (id - 1) * sizeof(struct Employee), SEEK_SET);
    fread(&emp, sizeof(struct Employee), 1, file);

    if (emp.id == 0) {
        printf("Employee not found\n");
        return;
    }

    printf("Employee ID: %d\n", emp.id);
    printf("Employee Name: %s\n", emp.name);
    printf("Employee Salary: %.2f\n", emp.salary);
}

int main() {
    FILE *file = fopen("employee_records.dat", "r+");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    int choice;
    while (1) {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEmployee(file);
                break;
            case 2:
                modifyEmployee(file);
                break;
            case 3:
                deleteEmployee(file);
                break;
            case 4:
                viewEmployeeDetails(file);
                break;
            case 5:
                fclose(file);
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
