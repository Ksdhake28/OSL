#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_READERS 5
#define NUM_WRITERS 3

pthread_mutex_t mutex;
sem_t readTry;
sem_t resource;
int readCount = 0;

void *reader(void *id) {
    int readerId = *((int *)id);

    while (1) {
    sem_wait(&readTry);
    pthread_mutex_lock(&mutex);
    readCount++;
    if (readCount == 1) {
        sem_wait(&resource);
    }
    pthread_mutex_unlock(&mutex);
    sem_post(&readTry);
    printf("Reader %d is reading.\n", readerId);
    sleep(1);
    pthread_mutex_lock(&mutex);
    readCount--;
    if (readCount == 0) {
        sem_post(&resource);
    }
    pthread_mutex_unlock(&mutex);
    sleep(2);
    }
}
void *writer(void *id) {
    int writerId = *((int *)id);
    while (1) {
        sem_wait(&resource);
        printf("Writer %d is writing.\n", writerId);
        sleep(2);
        sem_post(&resource);
        sleep(1);
    }
}
int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];

    int reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&readTry, 0, 1);
    sem_init(&resource, 0, 1);
    
    for (int i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, (void *)&reader_ids[i]);
    }
    for (int i = 0; i < NUM_WRITERS; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, (void *)&writer_ids[i]);
    }
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
    sem_destroy(&readTry);
    sem_destroy(&resource);
    return 0;
}