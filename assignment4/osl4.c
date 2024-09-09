#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>  // For sleep()

#define BUFFER_SIZE 10

// Shared buffer and its associated variables
int buffer[BUFFER_SIZE];
int in = 0;  // Index where the next item will be produced
int out = 0; // Index where the next item will be consumed

// Semaphores and mutex
sem_t empty;  // Semaphore to count empty slots in the buffer
sem_t full;   // Semaphore to count full slots in the buffer
pthread_mutex_t mutex;  // Mutex to protect access to buffer

void printArray1() {
    int loop1;
    for(loop1 = 0; loop1 < 10; loop1++)
        printf("%d\t", buffer[loop1]);
    printf("\n");
}

void printArray2() {
    int loop2;
    for(loop2 = 0; loop2 < 10; loop2++)
        printf("%d\t", buffer[loop2]);
    printf("\n");
}

// Producer function
void* producer(void* arg) {
    int item;
    while (1) {
        item = rand() % 100;  // Produce a random item
        sem_wait(&empty);     // Wait for an empty slot
        pthread_mutex_lock(&mutex); // Lock the mutex

        // Add the item to the buffer
        buffer[in] = item;
        printf("Produced: %d by thread %lu\n", item, pthread_self());
        printArray1();

        in = (in + 1) % BUFFER_SIZE; // Move to the next slot

        pthread_mutex_unlock(&mutex); // Unlock the mutex
        sem_post(&full);  // Signal that the buffer has one more full slot

        sleep(2);  // Sleep for a while to simulate production time
    }
    return NULL;
}

// Consumer function
void* consumer(void* arg) {
    int item;
    while (1) {
        sem_wait(&full);      // Wait for a full slot
        pthread_mutex_lock(&mutex);  // Lock the mutex

        // Remove the item from the buffer
        item = buffer[out];
        buffer[out] = 0;
        printf("Consumed: %d by thread %lu\n", item, pthread_self());
        printArray2();

        out = (out + 1) % BUFFER_SIZE; // Move to the next slot

        pthread_mutex_unlock(&mutex); // Unlock the mutex
        sem_post(&empty);  // Signal that the buffer has one more empty slot

        sleep(3);  // Sleep for a while to simulate consumption time
    }
    return NULL;
}

int main() {
    pthread_t prod1, cons1, prod2, cons2, prod3, cons3;

    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE);  // Initially, all slots are empty
    sem_init(&full, 0, 0);             // Initially, no slots are full

    // Initialize mutex
    pthread_mutex_init(&mutex, NULL);

    // Create producer and consumer threads
    pthread_create(&prod1, NULL, producer, NULL);
    pthread_create(&cons1, NULL, consumer, NULL);
    pthread_create(&prod2, NULL, producer, NULL);
    pthread_create(&cons2, NULL, consumer, NULL);
    pthread_create(&prod3, NULL, producer, NULL);
    pthread_create(&cons3, NULL, consumer, NULL);

    // Wait for threads to finish (which they never will in this example)
    pthread_join(prod1, NULL);
    pthread_join(cons1, NULL);
    pthread_join(prod2, NULL);
    pthread_join(cons2, NULL);
    pthread_join(prod3, NULL);
    pthread_join(cons3, NULL);

    // Cleanup
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
