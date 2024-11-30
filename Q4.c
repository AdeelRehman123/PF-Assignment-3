#include <stdio.h>
#include <stdlib.h>

void inputEmployees(int** ratings, int numEmployees, int numPeriods) {
    for (int i = 0; i < numEmployees; i++) {
        printf("\nEnter ratings for Employee %d:\n", i + 1);
        for (int j = 0; j < numPeriods; j++) {
            int score;
            do {
                printf("Rating for Period %d (1-10): ", j + 1);
                scanf("%d", &score);
                if (score < 1 || score > 10) {
                    printf("Invalid rating! Please enter a score between 1 and 10.\n");
                }
            } while (score < 1 || score > 10);
            ratings[i][j] = score;
        }
    }
}

void displayPerformance(int** ratings, int numEmployees, int numPeriods) {
    printf("\nPerformance Ratings:\n");
    for (int i = 0; i < numEmployees; i++) {
        printf("Employee %d: ", i + 1);
        for (int j = 0; j < numPeriods; j++) {
            printf("%d ", ratings[i][j]);
        }
        printf("\n");
    }
}

void findEmployeeOfTheYear(int** ratings, int numEmployees, int numPeriods) {
    double bestAverage = 0;
    int bestEmployees[numEmployees];
    int numBestEmployees = 0;

    for (int i = 0; i < numEmployees; i++) {
        int total = 0;
        for (int j = 0; j < numPeriods; j++) {
            total += ratings[i][j];
        }
        double average = (double)total / numPeriods;
        
        if (average > bestAverage) {
            bestAverage = average;
            numBestEmployees = 1;
            bestEmployees[0] = i;
        } else if (average == bestAverage) {
            bestEmployees[numBestEmployees] = i;
            numBestEmployees++;
        }
    }

    printf("\nEmployee(s) of the Year: ");
    for (int i = 0; i < numBestEmployees; i++) {
        printf("Employee %d ", bestEmployees[i] + 1);
    }
    printf("\n");
}

void findHighestRatedPeriod(int** ratings, int numEmployees, int numPeriods) {
    double bestAverage = 0;
    int bestPeriods[numPeriods];
    int numBestPeriods = 0;

    for (int j = 0; j < numPeriods; j++) {
        int total = 0;
        for (int i = 0; i < numEmployees; i++) {
            total += ratings[i][j];
        }
        double average = (double)total / numEmployees;

        if (average > bestAverage) {
            bestAverage = average;
            numBestPeriods = 1;
            bestPeriods[0] = j;
        } else if (average == bestAverage) {
            bestPeriods[numBestPeriods] = j;
            numBestPeriods++;
        }
    }

    printf("Highest Rated Evaluation Period(s): ");
    for (int i = 0; i < numBestPeriods; i++) {
        printf("Period %d ", bestPeriods[i] + 1);
    }
    printf("\n");
}

void findWorstPerformingEmployee(int** ratings, int numEmployees, int numPeriods) {
    double worstAverage = 10;
    int worstEmployees[numEmployees];
    int numWorstEmployees = 0;

    for (int i = 0; i < numEmployees; i++) {
        int total = 0;
        for (int j = 0; j < numPeriods; j++) {
            total += ratings[i][j];
        }
        double average = (double)total / numPeriods;

        if (average < worstAverage) {
            worstAverage = average;
            numWorstEmployees = 1;
            worstEmployees[0] = i;
        } else if (average == worstAverage) {
            worstEmployees[numWorstEmployees] = i;
            numWorstEmployees++;
        }
    }

    printf("Worst Performing Employee(s): ");
    for (int i = 0; i < numWorstEmployees; i++) {
        printf("Employee %d ", worstEmployees[i] + 1);
    }
    printf("\n");
}
int main() {
    int nemp, nper;

    printf("Enter the number of employees: ");
    scanf("%d", &nemp);
    printf("Enter the number of evaluation periods: ");
    scanf("%d", &nper);

    int **rating = (int **)malloc(nemp * sizeof(int *));
    for (int i = 0; i < nemp; i++) {
        rating[i] = (int *)malloc(nper * sizeof(int));
    }

    inputEmployees(rating, nemp, nper);
    displayPerformance(rating, nemp, nper);

    findEmployeeOfTheYear(rating, nemp, nper);
    findHighestRatedPeriod(rating, nemp, nper);
    findWorstPerformingEmployee(rating, nemp, nper);

    for (int i = 0; i < nper; i++) {
        free(rating[i]);
    }
    free(rating);

    return 0;
}

