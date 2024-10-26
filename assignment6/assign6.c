#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Function prototypes
void fifo(int frameSize, int ref[], int n);
void lru(int frameSize, int ref[], int n);
void optimal(int frameSize, int ref[], int n);
void printTable(int frameSize, int refSize, int hitFlag[], int frame[][refSize]);
void runTestCase();

int main()
{
    int n, frameSize, *ref;
    int choice;

    printf("\nPage Replacement Algorithm\n");
    printf("=====================================\n");

    printf("Enter the size of the reference string: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Invalid input. Reference string size must be positive.\n");
        return 1;
    }

    ref = (int *)malloc(n * sizeof(int));
    if (ref == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter the reference string: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &ref[i]);
    }

    printf("Enter the frame size: ");
    scanf("%d", &frameSize);

    if (frameSize <= 0 || frameSize > n)
    {
        printf("Invalid input. Frame size must be positive and not larger than the reference string size.\n");
        free(ref);
        return 1;
    }

    do
    {
        printf("\nMENU\n");
        printf("1 - FIFO\n");
        printf("2 - LRU\n");
        printf("3 - Optimal\n");
        printf("4 - Run Test Case\n");
        printf("5 - Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("\nPage Replacement using FIFO Algorithm\n");
            fifo(frameSize, ref, n);
            break;
        case 2:
            printf("\nPage Replacement using LRU Algorithm\n");
            lru(frameSize, ref, n);
            break;
        case 3:
            printf("\nPage Replacement using Optimal Algorithm\n");
            optimal(frameSize, ref, n);
            break;
        case 4:
            runTestCase();
            break;
        case 5:
            printf("\nExiting...\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    free(ref);
    return 0;
}

void fifo(int frameSize, int ref[], int n)
{
    int frame[frameSize][n];
    int hitFlag[n];
    int pageFaults = 0;
    int index = 0;

    // Initialize frames and hitFlag
    for (int i = 0; i < frameSize; i++)
        for (int j = 0; j < n; j++)
            frame[i][j] = -1;
    
    for (int i = 0; i < n; i++)
        hitFlag[i] = 0;

    for (int i = 0; i < n; i++)
    {
        int page = ref[i];
        int hit = 0;

        // Check if page is already in frame
        for (int j = 0; j < frameSize; j++)
        {
            if (frame[j][i] == page)
            {
                hit = 1;
                hitFlag[i] = 1;
                break;
            }
        }

        if (!hit)
        {
            pageFaults++;
            frame[index][i] = page;
            index = (index + 1) % frameSize;
        }

        // Copy frame state for next iteration
        if (i < n - 1)
        {
            for (int j = 0; j < frameSize; j++)
                frame[j][i + 1] = frame[j][i];
        }
    }

    printTable(frameSize, n, hitFlag, frame);
    printf("Total Page Faults: %d\n", pageFaults);
    printf("Hit Ratio: %.2f%%\n", (float)(n - pageFaults) / n * 100);
    printf("Miss Ratio: %.2f%%\n", (float)(pageFaults) / n * 100);
}

void lru(int frameSize, int ref[], int n)
{
    int frame[frameSize][n];
    int order[frameSize];
    int hitFlag[n];
    int pageFaults = 0;
    int time = 0;

    // Initialize frames, order, and hitFlag
    for (int i = 0; i < frameSize; i++)
    {
        order[i] = -1;
        for (int j = 0; j < n; j++)
            frame[i][j] = -1;
    }
    
    for (int i = 0; i < n; i++)
        hitFlag[i] = 0;

    for (int i = 0; i < n; i++)
    {
        int page = ref[i];
        int hit = 0;

        // Check if page is already in frame
        for (int j = 0; j < frameSize; j++)
        {
            if (frame[j][i] == page)
            {
                hit = 1;
                hitFlag[i] = 1;
                order[j] = time;
                break;
            }
        }

        if (!hit)
        {
            pageFaults++;
            int lru = 0;
            for (int j = 1; j < frameSize; j++)
            {
                if (order[j] < order[lru])
                    lru = j;
            }
            frame[lru][i] = page;
            order[lru] = time;
        }

        time++;

        // Copy frame state for next iteration
        if (i < n - 1)
        {
            for (int j = 0; j < frameSize; j++)
                frame[j][i + 1] = frame[j][i];
        }
    }

    printTable(frameSize, n, hitFlag, frame);
    printf("Total Page Faults: %d\n", pageFaults);
    printf("Hit Ratio: %.2f%%\n", (float)(n - pageFaults) / n * 100);
    printf("Miss Ratio: %.2f%%\n", (float)(pageFaults) / n * 100);

}

void optimal(int frameSize, int ref[], int n)
{
    int frame[frameSize][n];
    int hitFlag[n];
    int pageFaults = 0;

    // Initialize frames and hitFlag
    for (int i = 0; i < frameSize; i++)
        for (int j = 0; j < n; j++)
            frame[i][j] = -1;
    
    for (int i = 0; i < n; i++)
        hitFlag[i] = 0;

    for (int i = 0; i < n; i++)
    {
        int page = ref[i];
        int hit = 0;

        // Check if page is already in frame
        for (int j = 0; j < frameSize; j++)
        {
            if (frame[j][i] == page)
            {
                hit = 1;
                hitFlag[i] = 1;
                break;
            }
        }

        if (!hit)
        {
            pageFaults++;
            int replaceIndex = -1;
            int farthest = i;
            int empty = 0;

            for (int j = 0; j < frameSize; j++)
            {
                if (frame[j][i] == -1)
                {
                    replaceIndex = j;
                    empty = 1;
                    break;
                }

                int k;
                for (k = i + 1; k < n; k++)
                {
                    if (frame[j][i] == ref[k])
                        break;
                }

                if (k > farthest)
                {
                    farthest = k;
                    replaceIndex = j;
                }
            }

            frame[replaceIndex][i] = page;
        }

        // Copy frame state for next iteration
        if (i < n - 1)
        {
            for (int j = 0; j < frameSize; j++)
                frame[j][i + 1] = frame[j][i];
        }
    }

    printTable(frameSize, n, hitFlag, frame);
    printf("Total Page Faults: %d\n", pageFaults);
    printf("Hit Ratio: %.2f%%\n", (float)(n - pageFaults) / n * 100);
    printf("Miss Ratio: %.2f%%\n", (float)(pageFaults) / n * 100);
}

void printTable(int frameSize, int refSize, int hitFlag[], int frame[][refSize])
{
    printf("\nPage Replacement Table:\n");
    printf("------------------------\n");

    // Print header
    // printf("Ref:\t");
    // for (int i = 0; i < refSize; i++)
    //     printf("%d\t", frame[0][i]);
    // printf("\n");

    // Print frames
    for (int i = 0; i < frameSize; i++)
    {
        printf("Frame %d:", i);
        for (int j = 0; j < refSize; j++)
        {
            if (frame[i][j] == -1)
                printf("\t-");
            else
                printf("\t%d", frame[i][j]);
        }
        printf("\n");
    }

    // Print hit/miss
    printf("Status:\t");
    for (int i = 0; i < refSize; i++)
        printf("\t%s", hitFlag[i] ? "Hit" : "Miss");
    printf("\n");
}

void runTestCase()
{
    int testRef[] = {4, 7, 6, 1, 7, 6, 1, 2, 7, 2};
    int testFrameSize = 3;
    int testN = sizeof(testRef) / sizeof(testRef[0]);

    printf("\nRunning test case:\n");
    printf("Reference string: ");
    for (int i = 0; i < testN; i++)
    {
        printf("%d ", testRef[i]);
    }
    printf("\nFrame size: %d\n", testFrameSize);

    printf("\nFIFO Algorithm:\n");
    fifo(testFrameSize, testRef, testN);

    printf("\nLRU Algorithm:\n");
    lru(testFrameSize, testRef, testN);

    printf("\nOptimal Algorithm:\n");
    optimal(testFrameSize, testRef, testN);
}
