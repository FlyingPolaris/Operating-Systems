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
        while (p->next != NULL)
        {
            p = p->next;
        }
        int slice = p->task->burst;
        run(p->task, slice);
        p->task->waiting_time = p->task->response_time = time;
        time += slice;
        p->task->turnaround_time = time;
        __sync_fetch_and_add(&total_response_time, p->task->response_time);
        __sync_fetch_and_add(&total_turnaround_time, p->task->turnaround_time);
        __sync_fetch_and_add(&total_waiting_time, p->task->waiting_time);
        delete (&task_list,p->task);
        free(p->task);
        p = task_list;
    }
}