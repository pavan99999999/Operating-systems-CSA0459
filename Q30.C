#include <stdio.h>
#include <pthread.h>

void *printHello(void *threadID) {
    long tid = (long)threadID;
    printf("Hello from thread %ld\n", tid);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[5];
    int rc;
    long t;

    for (t = 0; t < 5; t++) {
        rc = pthread_create(&threads[t], NULL, printHello, (void *)t);
        if (rc) {
            printf("Error: Unable to create thread %ld\n", t);
            return -1;
        }
    }

    pthread_exit(NULL);
}




#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 5

void *printHello(void *threadID) {
    long tid = (long)threadID;
    printf("Hello from thread %ld\n", tid);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;

    for (t = 0; t < NUM_THREADS; t++) {
        rc = pthread_create(&threads[t], NULL, printHello, (void *)t);
        if (rc) {
            printf("Error: Unable to create thread %ld\n", t);
            return -1;
        }
    }

    for (t = 0; t < NUM_THREADS; t++) {
        rc = pthread_join(threads[t], NULL);
        if (rc) {
            printf("Error: Unable to join thread %ld\n", t);
            return -1;
        }
    }

    printf("All threads joined.\n");
    pthread_exit(NULL);
}





#include <stdio.h>
#include <pthread.h>

void *printHello(void *threadID) {
    pthread_t tid = pthread_self();
    printf("Hello from thread %lu\n", tid);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[2];
    int rc;

    rc = pthread_create(&threads[0], NULL, printHello, NULL);
    if (rc) {
        printf("Error: Unable to create thread 0\n");
        return -1;
    }

    rc = pthread_create(&threads[1], NULL, printHello, NULL);
    if (rc) {
        printf("Error: Unable to create thread 1\n");
        return -1;
    }

    if (pthread_equal(threads[0], threads[1])) {
        printf("Threads are equal.\n");
    } else {
        printf("Threads are not equal.\n");
    }

    pthread_exit(NULL);
}


#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 5

void *printHello(void *threadID) {
    long tid = (long)threadID;
    printf("Hello from thread %ld\n", tid);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;

    for (t = 0; t < NUM_THREADS; t++) {
        rc = pthread_create(&threads[t], NULL, printHello, (void *)t);
        if (rc) {
            printf("Error: Unable to create thread %ld\n", t);
            return -1;
        }
    }

    pthread_exit(NULL);
}
