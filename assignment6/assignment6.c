#include <stdio.h>
#include <stdlib.h>

#define MAX_PAGES 100

// Function to find page faults using FIFO
int FIFO(int pages[], int n, int capacity) {
    int *s = (int *)malloc(capacity * sizeof(int));
    int page_faults = 0;
    int size = 0;
    int front = 0;

    for (int i = 0; i < capacity; i++) {
        s[i] = -1; // Marking unused pages
    }

    for (int i = 0; i < n; i++) {
        int current_page = pages[i];
        int found = 0;

        for (int j = 0; j < size; j++) {
            if (s[j] == current_page) {
                found = 1;
                break;
            }
        }

        if (!found) {
            if (size < capacity) {
                s[size++] = current_page;
            } else {
                s[front] = current_page;
                front = (front + 1) % capacity;
            }
            page_faults++;
        }

        // Display current pages
        printf("Current pages: ");
        for (int j = 0; j < capacity; j++) {
            if (s[j] != -1) {
                printf("%d ", s[j]);
            }
        }
        printf("\n");
    }

    printf("Total iterations: %d\n", n);
    free(s);
    return page_faults;
}

// Function to find page faults using LRU
int LRU(int pages[], int n, int capacity) {
    int *s = (int *)malloc(capacity * sizeof(int));
    int page_faults = 0;
    int size = 0;
    int *last_used = (int *)malloc(capacity * sizeof(int));

    for (int i = 0; i < capacity; i++) {
        s[i] = -1; // Marking unused pages
        last_used[i] = 0; // Initialize last used times
    }

    for (int i = 0; i < n; i++) {
        int current_page = pages[i];
        int found = 0;

        for (int j = 0; j < size; j++) {
            if (s[j] == current_page) {
                found = 1;
                last_used[j] = i; // Update last used time
                break;
            }
        }

        if (!found) {
            if (size < capacity) {
                s[size] = current_page;
                last_used[size++] = i; // Update last used time
            } else {
                // Find the least recently used page
                int lru_index = 0;
                for (int j = 1; j < capacity; j++) {
                    if (last_used[j] < last_used[lru_index]) {
                        lru_index = j;
                    }
                }
                s[lru_index] = current_page; // Replace the LRU page
                last_used[lru_index] = i; // Update last used time
            }
            page_faults++;
        }

        // Display current pages
        printf("Current pages: ");
        for (int j = 0; j < capacity; j++) {
            if (s[j] != -1) {
                printf("%d ", s[j]);
            }
        }
        printf("\n");
    }

    printf("Total iterations: %d\n", n);
    free(s);
    free(last_used);
    return page_faults;
}

// Function to find page faults using Optimal Page Replacement
int Optimal(int pages[], int n, int capacity) {
    int *s = (int *)malloc(capacity * sizeof(int));
    int page_faults = 0;
    int size = 0;

    for (int i = 0; i < capacity; i++) {
        s[i] = -1; // Marking unused pages
    }

    for (int i = 0; i < n; i++) {
        int current_page = pages[i];
        int found = 0;

        // Check if the page is already in the set
        for (int j = 0; j < size; j++) {
            if (s[j] == current_page) {
                found = 1;
                break;
            }
        }

        if (!found) {
            if (size < capacity) {
                s[size++] = current_page; // Add the new page
            } else {
                // Find the optimal page to replace
                int farthest_index = -1;
                int page_to_replace = -1;

                for (int j = 0; j < size; j++) {
                    int k;
                    for (k = i + 1; k < n; k++) {
                        if (s[j] == pages[k]) {
                            if (farthest_index < k) {
                                farthest_index = k; // Update farthest index
                                page_to_replace = j; // Update page to replace
                            }
                            break; // Break inner loop as we found it
                        }
                    }
                    if (k == n) { // If the page is not found in future references
                        page_to_replace = j; // This page can be replaced
                        break; // Break as we found a page not used in the future
                    }
                }

                s[page_to_replace] = current_page; // Replace the optimal page
            }
            page_faults++;
        }

        // Display current pages
        printf("Current pages: ");
        for (int j = 0; j < capacity; j++) {
            if (s[j] != -1) {
                printf("%d ", s[j]);
            }
        }
        printf("\n");
    }

    printf("Total iterations: %d\n", n);
    free(s);
    return page_faults;
}

// Function to calculate the hit ratio
float HitRatio(int n, int faults) {
    return (float)(n - faults) / n; // Calculate hit ratio as a float
}

// Function to calculate the miss ratio
float MissRatio(int n, int faults) {
    return (float)faults / n; // Calculate miss ratio as a float
}

// Driver code
int main() {
    int pages[] = {4, 7, 6, 1, 7, 6, 1, 2, 7, 2};
    int n = sizeof(pages) / sizeof(pages[0]);

    int capacity;   
    printf("Enter number of page frames: ");
    scanf("%d", &capacity);
    
    printf("\nChoose an algorithm:\n");
    printf("1. FIFO\n");
    printf("2. LRU\n");
    printf("3. Optimal\n");
    printf("Enter your choice: ");
    int choice;
    scanf("%d", &choice);
    
    int faults = 0;
    switch (choice) {
        case 1:
            faults = FIFO(pages, n, capacity);
            break;
        case 2:
            faults = LRU(pages, n, capacity);
            break;
        case 3:
            faults = Optimal(pages, n, capacity);
            break;
        default:
            printf("Invalid choice.\n");
            return 1; // Exit with error
    }

    printf("\nTotal page faults: %d\n", faults);
    printf("Hit Ratio: %.2f\n", HitRatio(n, faults));
    printf("Miss Ratio: %.2f\n", MissRatio(n, faults));

    return 0;
}

