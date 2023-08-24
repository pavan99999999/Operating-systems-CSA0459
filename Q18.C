#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 4
#define NUM_ITERATIONS 5

int sharedCounter = 0;
pthread_mutex_t mutex;

void *incrementCounter(void *arg) {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        pthread_mutex_lock(&mutex);

        sharedCounter++;
        printf("Thread %ld: Incremented counter to %d\n", (long)arg, sharedCounter);

        pthread_mutex_unlock(&mutex);

        // Introduce some delay to simulate processing
        usleep(rand() % 100000);
    }

    pthread_exit(NULL);
}

int main() {
    srand(time(NULL));

    pthread_t threads[NUM_THREADS];
    pthread_mutex_init(&mutex, NULL);

    for (long i = 0; i < NUM_THREADS; i++)
        pthread_create(&threads[i], NULL, incrementCounter, (void *)i);

    for (int i = 0; i < NUM_THREADS; i++)
        pthread_join(threads[i], NULL);

    pthread_mutex_destroy(&mutex);

    printf("Final counter value: %d\n", sharedCounter);

    return 0;
}
