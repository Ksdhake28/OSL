#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int count = 0;

sem_t empty;
sem_t full;
pthread_mutex_t mutex;

void *producer(void *param) {
    int item;
    while (1) {
        // Produce an item
        item = rand() % 100;
        sem_wait(&empty);            // Decrease empty count
        pthread_mutex_lock(&mutex);  // Enter critical section

        // Add item to the buffer
        buffer[count] = item;
        count++;
        printf("Producer produced %d\n", item);

        pthread_mutex_unlock(&mutex); // Exit critical section
        sem_post(&full);              // Increase full count

        sleep(1); // Sleep to simulate time taken to produce
    }
}

void *consumer(void *param) {
    int item;
    while (1) {
        sem_wait(&full);              // Decrease full count
        pthread_mutex_lock(&mutex);   // Enter critical section

        // Remove item from the buffer
        item = buffer[count - 1];
        count--;
        printf("Consumer consumed %d\n", item);

        pthread_mutex_unlock(&mutex); // Exit critical section
        sem_post(&empty);             // Increase empty count

        sleep(1); // Sleep to simulate time taken to consume
    }
}

int main() {
    pthread_t prod_thread, cons_thread;

    // Initialize the semaphores
    sem_init(&empty, 0, BUFFER_SIZE); // Initially, all buffer slots are empty
    sem_init(&full, 0, 0);            // Initially, no items are in the buffer

    // Initialize the mutex
    pthread_mutex_init(&mutex, NULL);

    // Create the producer and consumer threads
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    // Join the threads (this will keep the program running)
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    // Destroy the semaphores and mutex
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
