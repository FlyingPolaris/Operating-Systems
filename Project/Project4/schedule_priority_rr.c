#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "cpu.h"
#include "list.h"
#include "task.h"
#include "schedulers.h"

Node *task_list = NULL;

void add(char *name, int priority, int burst)
{
    Task *new_task = malloc(sizeof(Task));
    new_task->origin_burst = burst;
    new_task->name = name;
    new_task->priority = priority;
    new_task->response_time = new_task->turnaround_time = new_task->waiting_time = -1;
    new_task->burst = burst;
    new_task->tid = __sync_fetch_and_add(&task_tid, 1);
    insert(&task_list, new_task);
}

void schedule()
{
    int slice = QUANTUM;
    int time = 0;
    Node *p = task_list;
    while (p != NULL)
    {
        int biggest_priority = p->task->priority;
        Node *q = p;
        while (p->next != NULL)
        {
            p = p->next;
            if (p->task->priority >= biggest_priority)
            {
                biggest_priority = p->task->priority;
                q = p;
            }
        }
        if (q->task->burst > slice)
        {
            run(q->task, slice);
            if (q->task->response_time == -1)
                q->task->response_time = time;
            q->task->burst -= slice;
            time += slice;
            delete (&task_list, q->task);
            insert(&task_list, q->task);
        }
        else if (q->task->burst <= slice)
        {
            run(q->task, q->task->burst);
            if (q->task->response_time == -1)
                q->task->response_time = time;
            time += q->task->burst;
            q->task->turnaround_time = time;
            q->task->waiting_time = time - q->task->origin_burst;
            __sync_fetch_and_add(&total_response_time, q->task->response_time);
            __sync_fetch_and_add(&total_turnaround_time, q->task->turnaround_time);
            __sync_fetch_and_add(&total_waiting_time, q->task->waiting_time);
            delete (&task_list, q->task);
            free(q->task);
        }
        p = task_list;
    }
}