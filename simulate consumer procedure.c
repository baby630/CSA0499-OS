#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_BUFFER_SIZE 5
#define NUM_PRODUCE 10
#define NUM_CONSUME 10

sem_t empty, full, mutex;
int buffer[MAX_BUFFER_SIZE];
int in = 0, out = 0;

void *producer(void *arg) {
    for (int i = 0; i < NUM_PRODUCE; i++) {
        sem_wait(&empty);
        sem_wait(&mutex);

        // Produce an item and add it to the buffer
        buffer[in] = i;
        printf("Producer produced item %d\n", i);
        in = (in + 1) % MAX_BUFFER_SIZE;

        sem_post(&mutex);
        sem_post(&full);

        sleep(1);
    }
    return NULL;
}

void *consumer(void *arg) {
    for (int i = 0; i < NUM_CONSUME; i++) {
        sem_wait(&full);
        sem_wait(&mutex);

        // Consume an item from the buffer
        int item = buffer[out];
        printf("Consumer consumed item %d\n", item);
        out = (out + 1) % MAX_BUFFER_SIZE;

        sem_post(&mutex);
        sem_post(&empty);

        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t producer_thread, consumer_thread;
    sem_init(&empty, 0, MAX_BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}

output :
Producer produced item 0
Producer produced item 1
Producer produced item 2
Consumer consumed item 0
Consumer consumed item 1
Consumer consumed item 2
Producer produced item 3
Producer produced item 4
Producer produced item 5
Consumer consumed item 3
Consumer consumed item 4
Consumer consumed item 5
Producer produced item 6
Producer produced item 7
Producer produced item 8
Consumer consumed item 6
Consumer consumed item 7
Consumer consumed item 8
Producer produced item 9
Consumer consumed item 9
