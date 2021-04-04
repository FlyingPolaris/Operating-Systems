#include "buffer.h"
#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>

buffer_item buffer[BUFFER_SIZE];
sem_t empty;
sem_t full;
pthread_mutex_t mutex;
int rear, front;


void init()
{
    rear = front = 0;
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, 0);
}

int insert_item(buffer_item item)
{
    sem_wait(&empty);
    pthread_mutex_lock(&mutex);
    buffer[rear] = item;
    rear = (rear + 1) % BUFFER_SIZE;
    pthread_mutex_unlock(&mutex);
    sem_post(&full);
    return 0;
}

int remove_item(buffer_item *item)
{
    sem_wait(&full);
    pthread_mutex_lock(&mutex);
    *item = buffer[front];
    front = (front + 1) % BUFFER_SIZE;
    pthread_mutex_unlock(&mutex);
    sem_post(&empty);
    return 0;
}