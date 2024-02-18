#include "queue.h"

// Function to check if a number is prime
bool isPrime(int n) {
    if (n <= 1) {
        return false;
    }
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

void *enqueueFromStdin(void *arg) {
    queue queue = (Queue *)arg;
    int num;

    while (scanf("%d", &num) != EOF) enqueue(queue, num);

    for (int i = 0; i < 6; i++) enqueue(queue, -1); // 6 to make all threads stop

    return NULL;
}

void *primeCounter(void *arg) {
    queue queue = (Queue *)arg;
    int number;

    while (1) {
        number = dequeue(queue);
        if (number == -1) break;
        if (isPrime(number)) atomic_fetch_add(&queue->counter, 1);
    }
    return NULL;
}

int main() {
    queue queue = initQueue();
    pthread_t mainThread, first, second,
     third, fourth, fifth, sixth;
    
    pthread_create(&mainThread, NULL, enqueueFromStdin, queue);
    pthread_create(&first, NULL, primeCounter, queue);
    pthread_create(&second, NULL, primeCounter, queue);
    pthread_create(&third, NULL, primeCounter, queue);
    pthread_create(&fourth, NULL, primeCounter, queue);
    pthread_create(&fifth, NULL, primeCounter, queue);
    pthread_create(&sixth, NULL, primeCounter, queue);

    pthread_join(mainThread, NULL);
    pthread_join(first, NULL);
    pthread_join(second, NULL);
    pthread_join(third, NULL);
    pthread_join(fourth, NULL);
    pthread_join(fifth, NULL);
    pthread_join(sixth, NULL);


    printf("%d total primes.\n", queue->counter);

    freeQueue(queue);

    return 0;
}