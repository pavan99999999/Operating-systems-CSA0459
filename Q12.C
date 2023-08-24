#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

pthread_mutex_t chopsticks[NUM_PHILOSOPHERS];
pthread_t philosophers[NUM_PHILOSOPHERS];

void *philosopher(void *arg) {
    int id = *((int *)arg);
    int left_chopstick = id;
    int right_chopstick = (id + 1) % NUM_PHILOSOPHERS;

    while (1) {
        // Think
        printf("Philosopher %d is thinking\n", id);
        sleep(rand() % 3 + 1);

        // Pick up chopsticks
        pthread_mutex_lock(&chopsticks[left_chopstick]);
        pthread_mutex_lock(&chopsticks[right_chopstick]);

        // Eat
        printf("Philosopher %d is eating\n", id);
        sleep(rand() % 3 + 1);

        // Put down chopsticks
        pthread_mutex_unlock(&chopsticks[left_chopstick]);
        pthread_mutex_unlock(&chopsticks[right_chopstick]);
    }
}

int main() {
    srand(time(NULL));

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&chopsticks[i], NULL);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        int *id = malloc(sizeof(int));
        *id = i;
        pthread_create(&philosophers[i], NULL, philosopher, (void *)id);
    }

    // Let the simulation run for a while
    sleep(30);

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_cancel(philosophers[i]);
        pthread_join(philosophers[i], NULL);
        pthread_mutex_destroy(&chopsticks[i]);
    }

    return 0;
}
