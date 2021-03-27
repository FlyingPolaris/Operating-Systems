/**
 * Representation of a task in the system.
 */

#ifndef TASK_H
#define TASK_H

extern int task_tid;
extern int total_turnaround_time;
extern int total_waiting_time;
extern int total_response_time;
// representation of a task
typedef struct task {
    char *name;
    int tid;
    int priority;
    int burst;
    int turnaround_time;
    int waiting_time;
    int response_time;
    int origin_burst;
} Task;

#endif
