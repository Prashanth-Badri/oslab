#include <stdio.h>

#define MAX_RESOURCES 10
#define MAX_PROCESSES 10

// Data structures for Banker's Algorithm
int available[MAX_RESOURCES];
int maximum[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];

// Function to initialize data structures
void initializeDataStructures(int numResources, int numProcesses) {
    // Initialize available resources
    printf("Enter available resources:\n");
    for (int i = 0; i < numResources; i++) {
        printf("Resource %d: ", i + 1);
        scanf("%d", &available[i]);
    }

    // Initialize maximum demand matrix
    printf("\nEnter maximum demand matrix:\n");
    for (int i = 0; i < numProcesses; i++) {
        printf("For Process %d:\n", i + 1);
        for (int j = 0; j < numResources; j++) {
            printf("Resource %d: ", j + 1);
            scanf("%d", &maximum[i][j]);
        }
    }

    // Initialize allocation matrix
    printf("\nEnter allocation matrix:\n");
    for (int i = 0; i < numProcesses; i++) {
        printf("For Process %d:\n", i + 1);
        for (int j = 0; j < numResources; j++) {
            printf("Resource %d: ", j + 1);
            scanf("%d", &allocation[i][j]);

            // Calculate need matrix
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }
}

// Function to display data in table format
void displayTable(int numResources, int numProcesses) {
    printf("\nTable Format:\n");

    // Display header
    printf("\nProc\t\tAlloc\t\tMax\t\t\tNeed\n");
   // for (int i = 0; i < numResources; i++) {
    //    printf("Resource %d  ", i + 1);
   // }
    printf("\n");

    // Display data
    for (int i = 0; i < numProcesses; i++) {
        printf("P%d\t\t", i + 1);

        // Display Allocation
        for (int j = 0; j < numResources; j++) {
            printf("%d  ", allocation[i][j]);
        }

        // Display Maximum
        printf("\t\t");
        for (int j = 0; j < numResources; j++) {
            printf("%d  ", maximum[i][j]);
        }

        // Display Need
        printf("\t\t");
        for (int j = 0; j < numResources; j++) {
            printf("%d  ", need[i][j]);
        }

        printf("\n");
    }
}

int main() {
    int numResources, numProcesses;

    printf("Enter the number of resources: ");
    scanf("%d", &numResources);

    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);

    initializeDataStructures(numResources, numProcesses);
    displayTable(numResources, numProcesses);

    return 0;
}
