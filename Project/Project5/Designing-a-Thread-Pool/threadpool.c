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
task worktodo;
pthread_mutex_t mutex;
sem_t full;
sem_t empty;

// the worker bee
pthread_t bee[NUMBER_OF_THREADS];
int rear, front;

// insert a task into the queue
// returns 0 if successful or 1 otherwise,
int enqueue(task t)
{
    pthread_mutex_lock(&mutex);
    workqueue[rear] = t;
    rear = (rear + 1) % QUEUE_SIZE;
    pthread_mutex_unlock(&mutex);
    return 0;
}

// remove a task from the queue
task dequeue()
{
    pthread_mutex_lock(&mutex);
    worktodo = workqueue[front];
    front = (front + 1) % NUMBER_OF_THREADS;
    pthread_mutex_unlock(&mutex);
    return worktodo;
}

// the worker thread in the thread pool
void *worker(void *param)
{
    // execute the task
    execute(worktodo.function, worktodo.data);
    
    pthread_exit(0);
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
    worktodo.function = somefunction;
    worktodo.data = p;

    return 0;
}

// initialize the thread pool
void pool_init(void)
{
    rear = front = 0;
    sem_init(&full, 0, QUEUE_SIZE);
    sem_init(&empty, 0, 0);
    memset(workqueue, 0, sizeof(workqueue));
    for (int i = 0; i < NUMBER_OF_THREADS; ++i)
    {
        pthread_create(&bee[i], NULL, worker, NULL);
    }
}

// shutdown the thread pool
void pool_shutdown(void)
{
    pthread_join(bee, NULL);
}
