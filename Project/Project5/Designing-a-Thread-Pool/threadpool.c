/**
 * Implementation of thread pool.
 */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <semaphore.h>
#include "threadpool.h"

#define QUEUE_SIZE 10
#define NUMBER_OF_THREADS 3

#define TRUE 1

// this represents work that has to be
// completed by a thread in the pool
typedef struct
{
    void (*function)(void *p);
    void *data;
} task;

// the work queue
task workqueue[QUEUE_SIZE];



sem_t mutex;
sem_t full;
sem_t empty;
int shutdown;

// the worker bee
pthread_t bee[NUMBER_OF_THREADS];
int rear, front;
//int currentsize;

// insert a task into the queue
// returns 0 if successful or 1 otherwise,
void enqueue(task t)
{
    sem_wait(&empty);
    sem_wait(&mutex);
    workqueue[rear] = t;
    rear = (rear + 1) % QUEUE_SIZE;
    //currentsize++;
    sem_post(&mutex);
    sem_post(&full);
}

// remove a task from the queue
task dequeue()
{
    task work_to_dequeue;
    sem_wait(&full);
    sem_wait(&mutex);
    work_to_dequeue = workqueue[front];
    front = (front + 1) % QUEUE_SIZE;
    //currentsize--;
    sem_post(&mutex);
    sem_post(&empty);
    return work_to_dequeue;
}

// the worker thread in the thread pool
void *worker(void *param)
{
    // execute the task
    task work_to_do;
    while (TRUE)
    {
        work_to_do = dequeue();
        if (shutdown)
            pthread_exit(0);
        execute(work_to_do.function, work_to_do.data);
    }
}

/**
 * Executes the task provided to the thread pool
 */
void execute(void (*somefunction)(void *p), void *p)
{
    (*somefunction)(p);
}

/**
 * Submits work to the pool.
 */
int pool_submit(void (*somefunction)(void *p), void *p)
{
    task work_to_submit;
    work_to_submit.function = somefunction;
    work_to_submit.data = p;
    enqueue(work_to_submit);

    return 0;
}

// initialize the thread pool
void pool_init(void)
{
    shutdown = 0;
    //currentsize = 0;
    rear = front = 0;
    sem_init(&mutex, 0, 1);
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, QUEUE_SIZE);
    //memset(workqueue, 0, sizeof(workqueue));
    for (int i = 0; i < NUMBER_OF_THREADS; ++i)
    {
        pthread_create(&bee[i], NULL, worker, NULL);
    }
}

// shutdown the thread pool
void pool_shutdown(void)
{
    shutdown = 1;
    for (int i = 0; i < NUMBER_OF_THREADS; ++i)
        sem_post(&full);
    for (int i = 0; i < NUMBER_OF_THREADS; ++i)
        pthread_join(bee[i], NULL);
}
