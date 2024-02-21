#include "queue.h"

/**
 * Function to check if a number is prime
 * Input: int (n)
 * Output: bool (true/false)
*/
bool isPrime(int n) {
    if (n <= 1) return false; // Negative or 1 is not prime
    if (n == 2 || n == 3) return true; // 2, 3 are prime, and "return" before next if
    if (n % 2 == 0 || n % 3 == 0) return false; // If 2 or 3 are divisors of n then return false, 
                                                    // to "return" before the root n chack

    // No need to check above the root of n
    for (int i = 5; i * i <= n; i += 6) 
        if (n % i == 0 || n % (i + 2) == 0) return false;

    return true;
}

/**
 * Function to get numbers from stdin and enqueue them in parallel
 * Input: void* (arg)
 * Output: void* (the func pointer, NULL)
*/
void *enqueueFromStdin(void *arg) {
    queue queue = (Queue*)arg;
    int number;

    while (scanf("%d", &number) != EOF) enqueue(queue, number);

    for (int i = 0; i < 4; i++) enqueue(queue, -1); // 4 to make all threads stop

    return NULL;
}

/**
 * Function to dequeue numbers and run the func isPrime on them, and count the amount of prime numbers
 * Input: void* (arg)
 * Output: void* (the func pointer, NULL)
*/
void *primeCounter(void *arg) {
    queue queue = (Queue*)arg;

    while (true) {
        int number = dequeue(queue);
        if (number == -1) break;
        if (isPrime(number) == true) atomic_fetch_add(&(queue->counter), 1);
    }
    return NULL;
}

int main() {
    queue queue = initQueue();
    pthread_t mainThread, first, second,
     third, fourth, fifth, sixth, seventh;
    
    pthread_create(&mainThread, NULL, enqueueFromStdin, queue);
    pthread_create(&first, NULL, primeCounter, queue);
    pthread_create(&second, NULL, primeCounter, queue);
    pthread_create(&third, NULL, primeCounter, queue);

    pthread_join(mainThread, NULL);
    pthread_join(first, NULL);
    pthread_join(second, NULL);
    pthread_join(third, NULL);


    printf("%d total primes.\n", queue->counter);

    freeQueue(queue);

    return 0;
}