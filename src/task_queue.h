//
// task_queue.h
//

#ifndef TASK_QUEUE_H
#define TASK_QUEUE_H

#include <stdbool.h>
#include <pthread.h>

#define TASK_QUEUE_INITIAL_CAPACITY (1 << 3)

typedef struct
{
  void *ctx;
  void (*handler)(void *);
} task_t;

typedef struct
{
  int capacity;
  int count;
  task_t *tasks;
  pthread_mutex_t mutex;
  pthread_cond_t cond;
} task_queue_t;

task_t task_new(void *ctx, void (*handler)(void *));
void task_queue_init(task_queue_t *queue);
void task_queue_free(task_queue_t *queue);
void task_queue_enqueue(task_queue_t *queue, task_t task);
task_t task_queue_dequeue(task_queue_t *queue);

#endif // TASK_QUEUE_H
