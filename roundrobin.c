#include <stdio.h>

int main() {
    int n, tq;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter time quantum: ");
    scanf("%d", &tq);

    int pid[n], at[n], bt[n], rt[n], ct[n], tat[n], wt[n], done[n];
    int gantt_pid[100], gantt_start[100], gantt_end[100];
    int chartIndex = 0;

    printf("Enter PIDs: ");
    for (int i = 0; i < n; i++) scanf("%d", &pid[i]);

    printf("Enter Arrival Times: ");
    for (int i = 0; i < n; i++) scanf("%d", &at[i]);

    printf("Enter Burst Times: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &bt[i]);
        rt[i] = bt[i];   // remaining time
        done[i] = 0;
    }

    int completed = 0, time = 0;

    while (completed < n) {
        int executed = 0;

        for (int i = 0; i < n; i++) {
            if (rt[i] > 0 && at[i] <= time) {
                int exec_time = (rt[i] > tq) ? tq : rt[i];

                gantt_pid[chartIndex] = pid[i];
                gantt_start[chartIndex] = time;
                gantt_end[chartIndex] = time + exec_time;
                chartIndex++;

                time += exec_time;
                rt[i] -= exec_time;

                if (rt[i] == 0 && done[i] == 0) {
                    ct[i] = time;
                    tat[i] = ct[i] - at[i];
                    wt[i] = tat[i] - bt[i];
                    done[i] = 1;
                    completed++;
                }

                executed = 1;
            }
        }

        if (!executed) {
            time++;
        }
    }

    float total_tat = 0, total_wt = 0;
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
        total_tat += tat[i];
        total_wt += wt[i];
    }

    printf("\nAverage Turnaround Time: %.2f", total_tat / n);
    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);

    // Print Gantt Chart
    printf("\nGantt Chart:\n");
    for (int i = 0; i < chartIndex; i++) {
        printf("| P%d ", gantt_pid[i]);
    }
    printf("|\n");

    for (int i = 0; i < chartIndex; i++) {
        printf("%d\t", gantt_start[i]);
    }
    printf("%d\n", gantt_end[chartIndex - 1]);

    return 0;
}
