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
    new_task->burst = burst;
    new_task->name = name;
    new_task->priority = priority;
    new_task->response_time = new_task->turnaround_time = new_task->waiting_time = 0;
    new_task->tid = __sync_fetch_and_add(&task_tid, 1);
    insert(&task_list, new_task);
}

void schedule()
{
    int time = 0;
    Node *p = task_list;
    while (p != NULL)
    {
        int shortest_burst = p->task->burst;
        Node *q = p;
        while (p->next != NULL)
        {
            p = p->next;
            if (p->task->burst <= shortest_burst)
            {
                shortest_burst = p->task->burst;
                q = p;
            }
        }
        int slice = q->task->burst;
        run(q->task, slice);
        q->task->waiting_time = q->task->response_time = time;
        time += slice;
        q->task->turnaround_time = time;
        __sync_fetch_and_add(&total_response_time, q->task->response_time);
        __sync_fetch_and_add(&total_turnaround_time, q->task->turnaround_time);
        __sync_fetch_and_add(&total_waiting_time, q->task->waiting_time);
        delete (&task_list, q->task);
        free(q->task);
        p = task_list;
    }
}
