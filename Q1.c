#include <stdio.h>
#include <string.h>
#include <time.h>

struct Emp {
    int employeeCode;
    char employeeName[100];
    char dateOfJoining[11]; 
};


void AssignUserDefine(struct Emp* emp) {
    printf("Enter Employee Code: ");
    scanf("%d", &emp->employeeCode);
    getchar();

    printf("Enter Employee Name: ");
    fgets(emp->employeeName, sizeof(emp->employeeName), stdin);
    emp->employeeName[strcspn(emp->employeeName, "\n")] = '\0';

    printf("Enter Date of Joining (DD-MM-YYYY): ");
    fgets(emp->dateOfJoining, sizeof(emp->dateOfJoining), stdin);
    emp->dateOfJoining[strcspn(emp->dateOfJoining, "\n")] = '\0'; 
}


int calculateTenure(char* dateOfJoining) {
    
    time_t t = time(NULL);
    struct tm* currentDate = localtime(&t);

    
    int day, month, year;
    sscanf(dateOfJoining, "%d-%d-%d", &day, &month, &year);

   
    int tenure = currentDate->tm_year + 1900 - year;

    
    if (currentDate->tm_mon + 1 < month || (currentDate->tm_mon + 1 == month && currentDate->tm_mday < day)) {
        tenure--;
    }

    return tenure;
}

int main() {
   
    struct Emp employees[4];

    
    for (int i = 0; i < 4; ++i) {
        printf("\nEnter details for Employee %d:\n", i + 1);
        AssignUserDefine(&employees[i]);
    }

    int count = 0;

    
    printf("\nEmployees with more than 3 years of tenure:\n");
    for (int i = 0; i < 4; ++i) {
        int tenure = calculateTenure(employees[i].dateOfJoining);
        if (tenure > 3) {
            printf("\nEmployee Code: %d\n", employees[i].employeeCode);
            printf("Employee Name: %s\n", employees[i].employeeName);
            printf("Date of Joining: %s\n", employees[i].dateOfJoining);
            printf("Tenure: %d years\n", tenure);
            count++;
        }
    }

    printf("\nTotal Employees with more than 3 years of tenure: %d\n", count);

    return 0;
}
