#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

#include "buffer.h"

int sleep_time, producer_num, consumer_num;
void *producer(void *param)
{
    buffer_item item;
    while (1)
    {
        sleep(rand() % sleep_time);
        item = rand();
        if (insert_item(item))
            fprintf(stderr, "report error condition");
        else
            printf("producer produced %d\n", item);
    }
}

void *consumer(void *param)
{
    buffer_item item;
    while (1)
    {
        sleep(rand() % sleep_time);
        if (remove_item(&item))
            fprintf(stderr, "report error condition");
        else
            printf("consumer consumed %d\n", item);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "report error condition");
        return -1;
    }

    srand((int)time(0));

    sleep_time = atoi(argv[1]);
    producer_num = atoi(argv[2]);
    consumer_num = atoi(argv[3]);

    init();

    pthread_t producers[producer_num];
    pthread_t consumers[consumer_num];

    for (int i = 0; i < producer_num; ++i)
    {
        pthread_create(&producers[i], 0, producer, 0);
    }

    for (int i = 0; i < consumer_num; ++i)
    {
        pthread_create(&consumers[i], 0, consumer, 0);
    }

    sleep(sleep_time);

    for (int i = 0; i < producer_num; i++)
        pthread_cancel(producers[i]);

    for (int i = 0; i < consumer_num; i++)
        pthread_cancel(consumers[i]);
    return 0;
}