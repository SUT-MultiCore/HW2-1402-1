#ifndef OPEN_MP_SCHEDULE_TASK_H
#define OPEN_MP_SCHEDULE_TASK_H


#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <malloc.h>
#include <omp.h>



struct task {
    uint64_t id;
    double start_time;
    double finish_time;

    // pointer to a function which indicates task action
    void (*action)(struct task *task);
};


typedef struct task task_t;

bool create_task(task_t *task);

bool destroy_task(task_t *task);

void task_start(task_t *task, double d);

void task_finish(task_t *task);

double response_time(task_t *task);


#endif //OPEN_MP_SCHEDULE_TASK_H
