#include<stdio.h>
#include<stdlib.h>
#define max 10

int main() {
    int np, ns;
    int allocation[max][max], maximum[max][max], need[max][max];
    int available[max], availability[max];
    int finish[max], safeSeq[max], count = 0;

    printf("Enter number of processes:\n");
    scanf("%d", &np);
    printf("Enter number of resources:\n");
    scanf("%d", &ns);

    // Initialize finish array
    for(int i = 0; i < np; i++)
        finish[i] = 0;

    // Input Allocation Matrix
    printf("Enter Allocation Matrix:\n");
    for(int i = 0; i < np; i++)
        for(int j = 0; j < ns; j++)
            scanf("%d", &allocation[i][j]);

    // Input Maximum Matrix
    printf("Enter Maximum Matrix:\n");
    for(int i = 0; i < np; i++)
        for(int j = 0; j < ns; j++)
            scanf("%d", &maximum[i][j]);

    // Input Available Resources
    printf("Enter Available Resources:\n");
    for(int j = 0; j < ns; j++)
        scanf("%d", &available[j]);

    // Calculate Need Matrix
    for(int i = 0; i < np; i++)
        for(int j = 0; j < ns; j++)
            need[i][j] = maximum[i][j] - allocation[i][j];

    // Display Input
    printf("Process\tAllocation\tMaximum\t\tNeed\n");
    for(int i = 0; i < np; i++) {
        printf("P%d\t", i);
        for(int j = 0; j < ns; j++)
            printf("%d", allocation[i][j]);
        printf("\t\t");
        for(int j = 0; j < ns; j++)
            printf("%d", maximum[i][j]);
        printf("\t\t");
        for(int j = 0; j < ns; j++)
            printf("%d", need[i][j]);
        printf("\n");
    }

    // Initialize availability
    for(int j = 0; j < ns; j++)
        availability[j] = available[j];

    // Banker's Safety Algorithm
    while(count < np) {
        int found = 0;
        for(int i = 0; i < np; i++) {
            if(finish[i] == 0) {
                int canAllocate = 1;
                for(int j = 0; j < ns; j++) {
                    if(need[i][j] > availability[j]) {
                        canAllocate = 0;
                        break;
                    }
                }

                if(canAllocate) {
                    for(int j = 0; j < ns; j++)
                        availability[j] += allocation[i][j];
                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if(!found) {
            printf("System is not in a safe state.\n");
            return 1;
        }
    }

    // Safe State Confirmed
    printf("System is in a safe state.\nSafe Sequence: ");
    for(int i = 0; i < np; i++)
        printf("P%d ", safeSeq[i]);
    printf("\n");

    return 0;
}
