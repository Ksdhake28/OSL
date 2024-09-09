#include <stdio.h>
#include <limits.h> // For INT_MAX
#define MAX 100
typedef struct {
    int id, arrival, burst, completion, waiting, turnAround;
} Process;

void sjfScheduling(Process p[], int n);
void rrScheduling(Process p[], int n, int quantum);
void printProcesses(Process p[], int n);
void printGanttChart(int gantt[], int n, int length);

int main() {
    int n, quantum;
    Process p[MAX];
    printf("Enter number of processes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        p[i].completion = 0; // Initialize completion time
        printf("Enter arrival time and burst time for Process %d: ", i + 1);
        scanf("%d %d", &p[i].arrival, &p[i].burst);
    }
    printf("Choose Scheduling Algorithm (1: SJF, 2: RR): ");
    scanf("%d", &quantum);
    if (quantum == 1) {
        sjfScheduling(p, n);
    } else if (quantum == 2) {
        printf("Enter time quantum for Round Robin: ");
        scanf("%d", &quantum);
        if (quantum <= 0) {
        printf("Time quantum must be positive.\n");
        return 1;
        }
        rrScheduling(p, n, quantum);
    } else {
        printf("Invalid choice.\n");
        return 1;
    }
        return 0;
}

void sjfScheduling(Process p[], int n) {
    int time = 0, completed = 0;
    float totalWaiting = 0, totalTurnAround = 0;
    while (completed < n) {
        int idx =-1, minBurst = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].completion == 0 && p[i].burst < minBurst) {
                minBurst = p[i].burst;
                idx = i;
            }
        }
        if (idx !=-1) {
            p[idx].completion = time + p[idx].burst;
            p[idx].turnAround = p[idx].completion- p[idx].arrival;
            p[idx].waiting = p[idx].turnAround- p[idx].burst;
            time += p[idx].burst;
            completed++;
            totalWaiting += p[idx].waiting;
            totalTurnAround += p[idx].turnAround;
        } else {
            time++; // Increment time if no process is ready
        }
    }
    printProcesses(p, n);
    printf("Avg Waiting Time: %.2f, Avg Turnaround Time: %.2f\n", totalWaiting / n,
    totalTurnAround / n);
}

void rrScheduling(Process p[], int n, int quantum) {
    int remaining[MAX], time = 0, completed = 0;
    float totalWaiting = 0, totalTurnAround = 0;
    int gantt[MAX * 10]; // Array to store Gantt chart (assuming a maximum size for simplicity)
    int ganttLength = 0;
    for (int i = 0; i < n; i++) remaining[i] = p[i].burst;
    while (completed < n) {
        int processHandled = 0;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && remaining[i] > 0) {
            processHandled = 1;
            if (remaining[i] <= quantum) {
                for (int j = 0; j < remaining[i]; j++) {
                gantt[ganttLength++] = p[i].id;
                }
            time += remaining[i];
            p[i].completion = time;
            p[i].turnAround = p[i].completion- p[i].arrival;
            p[i].waiting = p[i].turnAround- p[i].burst;
            remaining[i] = 0;
            completed++;
            } else {
                for (int j = 0; j < quantum; j++) {
                    gantt[ganttLength++] = p[i].id;
                }
                remaining[i]-= quantum;
                time += quantum;
                }
            }
        }
        if (!processHandled) {
            gantt[ganttLength++] = 0; // 0 represents idle time
            time++; // Increment time if no process is handled
        }
    }
    printProcesses(p, n);
    printGanttChart(gantt, n, ganttLength);
    for (int i = 0; i < n; i++) {
        totalWaiting += p[i].waiting;
        totalTurnAround += p[i].turnAround;
    }
    printf("Avg Waiting Time: %.2f, Avg Turnaround Time: %.2f\n", totalWaiting / n,
    totalTurnAround / n);
}

void printProcesses(Process p[], int n) {
    printf("\nPID | Arrival | Burst | Completion | Waiting | Turnaround\n");
    for (int i = 0; i < n; i++) {
        printf("%3d | %7d | %5d | %10d | %6d | %10d\n", p[i].id, p[i].arrival, p[i].burst,
        p[i].completion, p[i].waiting, p[i].turnAround);
    }
}

void printGanttChart(int gantt[], int n, int length) {
    printf("\nGantt Chart:\n");
    for (int i = 0; i < length; i++) {
        if (gantt[i] == 0) {
            printf("| Idle ");
        } else {
            printf("| P%d ", gantt[i]);
        }
    }
    printf("|\n");
    // Print timeline below the Gantt chart
    printf("0");
    for (int i = 1; i < length; i++) {
        printf("----");
    }
    printf("--\n");
}