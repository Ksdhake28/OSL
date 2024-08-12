#include<stdio.h>
#include<stdlib.h>
#define COLS 3
void sort(int n, int arr[][COLS]) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j][1] > arr[j + 1][1]) {
                int temp[COLS];
                for (int k = 0; k < COLS; k++) {
                    temp[k] = arr[j][k];
                    arr[j][k] = arr[j + 1][k];
                    arr[j + 1][k] = temp[k];
                }
            }
        }
    }
}

void SJF(int arr[][], int n){
    
}
// void SJF(int arr[][],int n){
// sort_burst(burst,n);
// int totalWaiting = 0, totalTurnaround = 0, currentTime = 0;
//     for (int i = 0; i < n; i++) {
//         p[i].waiting = currentTime - arrival[i];
//         p[i].turnaround = p[i].waiting + p[i].burst;
//         totalWaiting += p[i].waiting;
//         totalTurnaround += p[i].turnaround;
//         currentTime += p[i].burst;
//     }
// printf("Gantt chart for SJF : ");
// for(int i=0;i<n;i++){
// printf("%d\t",burst[i]);
// }
// }

int main(){
int n;
printf("Enter number of processes : ");
scanf("%d",&n);

int (*matrix)[COLS] = (int (*)[COLS])malloc(n * sizeof(*matrix));
    if (matrix == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

for (int i = 0; i < n; i++) {
        matrix[i][0] = i + 1;
        printf("Enter Arrival Time for Process ID: %d \n", i + 1);        
        scanf("%d", &matrix[i][1]);

        printf("Enter Burst Time for Process ID: %d \n", i + 1);
        scanf("%d", &matrix[i][2]);
}

printf("After sorting ");
// printf("\n%-10s %-15s %-10s\n", "ProcessID", "ArrivalTime", "BurstTime");
//     for (int i = 0; i < n; i++) {
//         printf("%-10d %-15d %-10d\n", matrix[i][0], matrix[i][1], matrix[i][2]);
//     }
    printf("\n%-10s %-15s %-10s\n", "ProcessID", "ArrivalTime", "BurstTime");
    for (int i = 0; i < n; i++) {
        printf("%-10d %-15d %-10d\n", matrix[i][0], matrix[i][1], matrix[i][2]);
    }
//SJF(arriavlburst,wait,n);

return 0;
}

// #include <stdio.h>

// // Define the Process structure
// typedef struct {
//     int id;         // Process ID
//     int arrival;    // Arrival time
//     int burst;      // Burst time
// } Process;

// void calculateRR(Process p[], int n, int quantum) {
//     int remainingBurst[n], waiting[n], turnaround[n];
//     int totalWaiting = 0, totalTurnaround = 0;
//     int currentTime = 0, count = 0;
//     int completedProcesses = 0;

//     // Initialize remaining burst times
//     for (int i = 0; i < n; i++) {
//         remainingBurst[i] = p[i].burst;
//         waiting[i] = 0;
//         turnaround[i] = 0;
//     }

//     while (completedProcesses < n) {
//         int allProcessed = 1;

//         for (int i = 0; i < n; i++) {
//             if (remainingBurst[i] > 0 && p[i].arrival <= currentTime) {
//                 allProcessed = 0;

//                 if (remainingBurst[i] <= quantum) {
//                     // Process completes in this quantum
//                     currentTime += remainingBurst[i];
//                     waiting[i] = currentTime - p[i].arrival - p[i].burst;
//                     turnaround[i] = waiting[i] + p[i].burst;
//                     remainingBurst[i] = 0;
//                     completedProcesses++;
//                     totalWaiting += waiting[i];
//                     totalTurnaround += turnaround[i];
//                 } else {
//                     // Process continues to next quantum
//                     remainingBurst[i] -= quantum;
//                     currentTime += quantum;
//                 }
//             }
//         }

//         // If no processes are ready to be executed, increment time
//         if (allProcessed) {
//             currentTime++;
//         }
//     }

//     printf("\nRound Robin Scheduling:\n");
//     for (int i = 0; i < n; i++) {
//         printf("Process %d: Arrival = %d, Burst = %d, Waiting = %d, Turnaround = %d\n",
//             p[i].id, p[i].arrival, p[i].burst, waiting[i], turnaround[i]);
//     }
//     printf("Average Waiting Time: %.2f\n", (float)totalWaiting / n);
//     printf("Average Turnaround Time: %.2f\n", (float)totalTurnaround / n);
// }

// int main() {
//     // Example usage
//     int n = 4; // Number of processes
//     Process p[] = {
//         {1, 0, 5},
//         {2, 1, 4},
//         {3, 2, 2},
//         {4, 4, 1}
//     };
//     int quantum = 2; // Time quantum for Round Robin

//     calculateRR(p, n, quantum);
//     return 0;
// }