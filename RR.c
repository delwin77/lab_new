#include <stdio.h>

#define MAX_PROCESSES 100

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
} Process;

void round_robin(Process processes[], int n, int quantum) {
    int time = 0;
    int completed = 0;
    int i = 0;
    int flag = 0;

    while (completed != n) {
        if (processes[i].remaining_time <= quantum && processes[i].remaining_time > 0) {
            time += processes[i].remaining_time;
            processes[i].remaining_time = 0;
            flag = 1;
        } else if (processes[i].remaining_time > 0) {
            processes[i].remaining_time -= quantum;
            time += quantum;
        }

        if (processes[i].remaining_time == 0 && flag == 1) {
            completed++;
            processes[i].completion_time = time;
            processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
            processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
            flag = 0;
        }

        if (i == n - 1)
            i = 0;
        else if (processes[i + 1].arrival_time <= time)
            i++;
        else
            i = 0;
    }
}

int main() {
    int n, quantum;
    Process processes[MAX_PROCESSES];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].pid = i + 1;
        processes[i].remaining_time = processes[i].burst_time;
    }

    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    round_robin(processes, n, quantum);

    float total_waiting_time = 0;
    float total_turnaround_time = 0;

    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].pid, processes[i].arrival_time, processes[i].burst_time,
               processes[i].completion_time, processes[i].waiting_time, processes[i].turnaround_time);
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }

    printf("\nAverage Waiting Time: %.2f\n", total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround_time / n);

    return 0;
}

