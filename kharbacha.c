#include <stdio.h>
#include <pthread.h>

void *make_coffee(void *arg) {
    int *coffee = (int *)arg;
    pthread_mutex_t *coffee_mutex = (pthread_mutex_t *)(arg + 1); // Incrementing the pointer by the size of int to access the mutex

    pthread_mutex_lock(coffee_mutex);
    (*coffee)++; // Increment the value of coffee, not the pointer itself
    pthread_mutex_unlock(coffee_mutex);
    return NULL;
}

int main() {
    int coffee = 0;
    pthread_t workers[100];
    pthread_mutex_t coffee_mutex;

    pthread_mutex_init(&coffee_mutex, NULL);

    for (int i = 0; i < 100; i++)
        pthread_create(&workers[i], NULL, make_coffee, (void *)&coffee_mutex); // Pass the address of coffee_mutex

    for (int i = 0; i < 100; i++)
        pthread_join(workers[i], NULL);

    printf("%d\n", coffee);

    pthread_mutex_destroy(&coffee_mutex); // Destroy the mutex after its usage

    return 0;
}
