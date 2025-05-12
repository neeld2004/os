#include <stdio.h>

struct process {
    int pid, at, ct, bt, wt, tat, done;
};

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct process p[n];

    printf("Enter process IDs: ");
    for (int i = 0; i < n; i++) scanf("%d", &p[i].pid);

    printf("Enter arrival times: ");
    for (int i = 0; i < n; i++) scanf("%d", &p[i].at);

    printf("Enter burst times: ");
    for (int i = 0; i < n; i++) scanf("%d", &p[i].bt);

    for (int i = 0; i < n; i++) p[i].done = 0;

    int completed = 0, time = 0;
    float total_tat = 0, total_wt = 0;

    // Gantt Chart tracking
    int gantt_pid[100], gantt_start[100], gantt_end[100];
    int chartIndex = 0;

    while (completed < n) {
        int min_bt = 9999, index = -1;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && !p[i].done && p[i].bt < min_bt) {
                min_bt = p[i].bt;
                index = i;
            }
        }

        if (index != -1) {
            gantt_pid[chartIndex] = p[index].pid;
            gantt_start[chartIndex] = time;

            time += p[index].bt;

            gantt_end[chartIndex] = time;
            chartIndex++;

            p[index].ct = time;
            p[index].tat = p[index].ct - p[index].at;
            p[index].wt = p[index].tat - p[index].bt;
            p[index].done = 1;

            total_tat += p[index].tat;
            total_wt += p[index].wt;

            completed++;
        } else {
            time++;
        }
    }

    // Output
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Turnaround Time: %.2f", total_tat / n);
    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);

    // Gantt Chart
    printf("\nGantt Chart:\n|");
    for (int i = 0; i < chartIndex; i++) {
        printf(" P%d |", gantt_pid[i]);
    }
    printf("\n");

    for (int i = 0; i < chartIndex; i++) {
        printf("%d\t", gantt_start[i]);
    }
    printf("%d\n", gantt_end[chartIndex - 1]);

    return 0;
}
