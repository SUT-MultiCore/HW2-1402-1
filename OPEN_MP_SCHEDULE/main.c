#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "task.h"


#define TASKS_NUM 1000
#define TEST_TIMES 10000


#define SCHEDULER dynamic

#define CHUNK_SIZE 1
//
//+---------------------------------------+
//| Mean Response Time: 0.967194 ms
//| Execution Time: 842.030348 ms
//+---------------------------------------+


/*============== UTILITY FUNCTIONS ==============*/


void unbalanced_action(task_t *task) {
    // gen a random number
    int random_number = (rand() * task->id) % 500;

    double counter = 0;

    for (int i = 0; i < random_number; i++) {
        counter += i * 1.2;
    }
}

void balanced_action(task_t *task) {
    // gen a random number
    int random_number = (task->id) % 500;

    double counter = 0;
    counter += random_number;
}


void gen_tasks(task_t *tasks, size_t size, void (*action)(task_t *task)) {
    for (int i = 0; i < size; i++) {
        tasks[i].id = i;
        tasks[i].action = action;
    }
}


double get_mean_response_time(task_t *tasks, size_t size) {
    double mean_response_time = 0;
    for (int i = 0; i < size; i++) {
        mean_response_time += response_time(&tasks[i]);
    }

    mean_response_time /= size;

    return mean_response_time;
}

void log_results(double time, double mean_response_time) {
    printf("Mean Response Time: %f\n", mean_response_time);
    printf("Execution Time: %f\n", time);

}

/*===============================================*/


void do_tasks(task_t *tasks, size_t size) {


    double start_time = omp_get_wtime();

#pragma omp parallel for default(none) shared(tasks)  firstprivate(size, start_time) schedule(SCHEDULER, CHUNK_SIZE)
    for (int i = 0; i < size; i++) {
        task_start(&tasks[i], start_time);
        tasks[i].action(&tasks[i]);
        task_finish(&tasks[i]);
    }


}


int main() {
    /* =================== OMP CONFIG ================ */
#ifndef _OPENMP
    printf("OpenMP is not supported.\n");
    exit(1);
#endif


    // get the number of threads
    int available_thread_num = omp_get_max_threads();

    // set the number of threads
    omp_set_num_threads(available_thread_num);
    /* =============================================== */



    double mean_time = 0;
    double mean_response = 0;
    for (int i = 0; i < TEST_TIMES; i++) {
        task_t tasks[TASKS_NUM];
        gen_tasks(tasks, TASKS_NUM, balanced_action);

        // start timer
        double start_time = omp_get_wtime();
        do_tasks(tasks, TASKS_NUM);
        double end_time = omp_get_wtime();

        double time = end_time - start_time;
        mean_time += time;

        double mean_response_time = get_mean_response_time(tasks, TASKS_NUM);
        mean_response += mean_response_time;

        log_results(time, mean_response_time);

    }

    mean_time /= TEST_TIMES;
    mean_response /= TEST_TIMES;

    printf("+---------------------------------------+\n");
    printf("| Mean Response Time: %f ms\n", mean_response * 1000);
    printf("| Execution Time: %f ms\n", mean_time * 1000);
    printf("+---------------------------------------+\n");


    return 0;
}