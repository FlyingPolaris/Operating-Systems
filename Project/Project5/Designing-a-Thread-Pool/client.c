/**
 * Example client program that uses thread pool.
 */

#include <stdio.h>
#include <unistd.h>
#include "threadpool.h"

struct data
{
    int a;
    int b;
};

void add(void *param)
{
    struct data *temp;
    temp = (struct data *)param;

    printf("I add two values %d and %d result = %d\n", temp->a, temp->b, temp->a + temp->b);
}

int main(void)
{
    // create some work to do
    pool_init();
    struct data work[100];
    for (int i = 0; i < 100; ++i)
    {
        work[i].a = i;
        work[i].b = i;
        // submit the work to the queue
        pool_submit(&add, &work[i]);
    }

    // may be helpful
    sleep(3);

    pool_shutdown();

    return 0;
}
