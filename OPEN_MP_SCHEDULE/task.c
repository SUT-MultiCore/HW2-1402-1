#include "task.h"


bool create_task(task_t *task) {
    if (task == NULL) {
        return false;
    }

    task->id = 0;
    task->start_time = 0;
    task->finish_time = 0;
    task->action = NULL;

    return true;
}

bool destroy_task(task_t *task) {
    if (task == NULL) {
        return false;
    }

    free(task);
    return true;
}

void task_start(task_t *task, double d) {
    if (task == NULL) {
        return;
    }

    task->start_time = d;
}

void task_finish(task_t *task) {
    if (task == NULL) {
        return;
    }

    task->finish_time = omp_get_wtime();
}

double response_time(task_t *task) {
    if (task == NULL) {
        return 0;
    }

    return task->finish_time - task->start_time;
}

