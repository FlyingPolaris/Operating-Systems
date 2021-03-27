/**
 * Driver.c
 *
 * Schedule is in the format
 *
 *  [name] [priority] [CPU burst]
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "task.h"
#include "list.h"
#include "schedulers.h"

#define SIZE 100

int main(int argc, char *argv[])
{
    FILE *in;
    char *temp;
    char task[SIZE];

    char *name;
    int priority;
    int burst;

    in = fopen(argv[1], "r");

    while (fgets(task, SIZE, in) != NULL)
    {
        temp = strdup(task);
        name = strsep(&temp, ",");
        priority = atoi(strsep(&temp, ","));
        burst = atoi(strsep(&temp, ","));

        // add the task to the scheduler's list of tasks
        add(name, priority, burst);

        free(temp);
    }

    fclose(in);

    // invoke the scheduler
    schedule();

    printf("Average turnaround time = %lf units.\n", 1.0 * total_turnaround_time / task_tid);
    printf("Average waiting time = %lf units.\n", 1.0 * total_waiting_time / task_tid);
    printf("Average response time = %lf units.\n", 1.0 * total_response_time / task_tid);

    return 0;
}
