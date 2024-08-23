#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Function to perform sorting (Selection Sort used here for demonstration)
void selectionSort(int arr[], int n) {
    int i, j, min_idx, temp;
    for (i = 0; i < n-1; i++) {
        min_idx = i;
        for (j = i+1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        // Swap the found minimum element with the first element
        temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

void selectionSortDesc(int arr[], int n) {
    int i, j, min_idx, temp;
    for (i = 0; i < n-1; i++) {
        min_idx = i;
        for (j = i+1; j < n; j++) {
            if (arr[j] > arr[min_idx]) {
                min_idx = j;
            }
        }
        // Swap the found minimum element with the first element
        temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    pid_t pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Child process sorting...\n");
        printf("Child process PID: %d \n",  getpid());
        selectionSort(arr, n);
        printf("Child process sorted array:\n");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
        printf("Child process exiting.\n");
        exit(0);
    } else {
        // Parent process
        printf("Parent process waiting for child...\n\n");
        int status;
        waitpid(pid, &status, 0);  // Wait for the child process to complete

        // Sorting in parent process using a different algorithm (Selection Sort Descending here)
        printf("\nParent process sorting...\n");
        printf("Parent process PID: %d \n", getpid());
        selectionSortDesc(arr, n);
        printf("Parent process sorted array:\n");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
        printf("Parent process exiting.\n");
    }

    return 0;
}