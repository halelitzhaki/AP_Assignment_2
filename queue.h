#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdatomic.h>


#define SIZE 1000

typedef struct Queue {
    // The array that will store the numbers from the generator
    int *array;
    int len;

    // For implementing circular array
    int front;
    int rear;

    // For working in parallel
    atomic_int counter; // Store the amount of prime numbers
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} Queue, *queue;

queue initQueue();
void enqueue(queue, int);
int dequeue(queue);
void freeQueue(queue);

#endif