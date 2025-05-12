#include <stdio.h>

struct Process {
    int Pid;
    int priority;
    int AT;
    int BT;
    int CT;
    int TAT;
    int WT;
    int RT;
    int StartTime;
};

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process P[n];
    int visited[n];
    int gantt[n]; // To store execution order

    printf("Input the process details:\n");
    for (int i = 0; i < n; i++) {
        printf("\nProcess %d:\n", i + 1);
        printf("Enter Process ID: ");
        scanf("%d", &P[i].Pid);

        printf("Enter Priority (higher number = higher priority): ");
        scanf("%d", &P[i].priority);

        printf("Enter Arrival Time: ");
        scanf("%d", &P[i].AT);

        printf("Enter Burst Time: ");
        scanf("%d", &P[i].BT);

        visited[i] = 0;
    }

    int currentTime = 0, lastExecutedProcess = -1, completed = 0;

    while (completed < n) {
        int index = -1;
        int maxPriority = -1;

        // First time, pick process with minimum AT
        if (completed == 0) {
            int minAT = 99999;
            for (int j = 0; j < n; j++) {
                if (P[j].AT < minAT) {
                    minAT = P[j].AT;
                    index = j;
                }
            }
            currentTime = P[index].AT;
        } else {
            currentTime = P[lastExecutedProcess].CT;
        }

        for (int j = 0; j < n; j++) {
            if (P[j].AT <= currentTime && visited[j] == 0) {
                if (P[j].priority > maxPriority) {
                    maxPriority = P[j].priority;
                    index = j;
                } else if (P[j].priority == maxPriority) {
                    if (P[j].AT < P[index].AT) {
                        index = j;
                    }
                }
            }
        }

        if (index != -1) {
            P[index].StartTime = currentTime;
            P[index].CT = currentTime + P[index].BT;
            P[index].TAT = P[index].CT - P[index].AT;
            P[index].WT = P[index].TAT - P[index].BT;
            P[index].RT = P[index].StartTime - P[index].AT;
            visited[index] = 1;
            gantt[completed] = index;
            lastExecutedProcess = index;
            completed++;
        } else {
            currentTime++;
        }
    }

    printf("\nProcess\tPriority\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t%d\t%d\t%d\t%d\t%d\n",
               P[i].Pid, P[i].priority, P[i].AT, P[i].BT, P[i].CT,
               P[i].TAT, P[i].WT, P[i].RT);
    }

    // Gantt Chart
    printf("\nGantt Chart:\n|");
    for (int i = 0; i < n; i++) {
        printf(" P%d |", P[gantt[i]].Pid);
    }
    printf("\n");

    // Timeline
    printf("%d", P[gantt[0]].StartTime);
    for (int i = 0; i < n; i++) {
        printf("   %d", P[gantt[i]].CT);
    }
    printf("\n");

    return 0;
}
