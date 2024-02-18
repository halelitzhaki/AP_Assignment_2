#include "queue.h"


queue initQueue() {
    queue queue = (Queue *)malloc(sizeof(Queue));
    if (queue == NULL) exit(0);

    queue->array = (int *)malloc(SIZE * sizeof(int));
    if (queue->array == NULL) {
        free(queue);
        exit(0);
    }

    queue->len = 0;
    queue->front = -1;
    queue->rear = -1;

    atomic_init(&queue->counter, 0);
    pthread_mutex_init(&queue->mutex, NULL);
    pthread_cond_init(&queue->cond, NULL);

    return queue;
}

void enqueue(queue queue, int value) {
    pthread_mutex_lock(&queue->mutex);

    while ((queue->rear + 1) % SIZE == queue->front) {
        pthread_cond_wait(&queue->cond, &queue->mutex);
    }

    if (queue->front == -1) {
        queue->front = 0;
        queue->rear = 0;
    } 
    else queue->rear = (queue->rear + 1) % SIZE;

    queue->array[queue->rear] = value;
    queue->len++;

    pthread_mutex_unlock(&queue->mutex);
    pthread_cond_signal(&queue->cond);
}

int dequeue(queue queue) {
    pthread_mutex_lock(&queue->mutex);

    while (queue->len == 0) {
        pthread_cond_wait(&queue->cond, &queue->mutex);
    }

    int value = queue->array[queue->front];
    if (queue->front == queue->rear) {
        queue->front = -1;
        queue->rear = -1;
    } 
    else queue->front = (queue->front + 1) % SIZE;

    queue->len--;

    pthread_mutex_unlock(&queue->mutex);
    pthread_cond_signal(&queue->cond);

    return value;
}

void freeQueue(queue queue) {
    free(queue->array);
    free(queue);
}