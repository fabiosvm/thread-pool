//
// task_queue.c
//

#include "task_queue.h"
#include <stdlib.h>
#include <assert.h>

task_t task_new(void *ctx, void (*handler)(void *))
{
  task_t task;
  task.ctx = ctx;
  task.handler = handler;
  return task;
}

void task_queue_init(task_queue_t *queue)
{
  queue->capacity = TASK_QUEUE_INITIAL_CAPACITY;
  queue->count = 0;
  queue->tasks = malloc(sizeof(*queue->tasks) * queue->capacity);
  assert(queue->tasks);
  pthread_mutex_init(&queue->mutex, NULL);
  pthread_cond_init(&queue->cond, NULL);
}

void task_queue_free(task_queue_t *queue)
{
  free(queue->tasks);
  pthread_mutex_destroy(&queue->mutex);
  pthread_cond_destroy(&queue->cond);
}

void task_queue_enqueue(task_queue_t *queue, task_t task)
{
  pthread_mutex_lock(&queue->mutex);
  if (queue->count == queue->capacity)
  {
    queue->capacity <<= 1;
    queue->tasks = realloc(queue->tasks, sizeof(*queue->tasks) * queue->capacity);
    assert(queue->tasks);
  }
  queue->tasks[queue->count] = task;
  ++queue->count;
  pthread_mutex_unlock(&queue->mutex);
  pthread_cond_signal(&queue->cond);
}

task_t task_queue_dequeue(task_queue_t *queue)
{
  pthread_mutex_lock(&queue->mutex);
  while (!queue->count)
    pthread_cond_wait(&queue->cond, &queue->mutex);
  task_t task = queue->tasks[0];
  for (int i = 0; i < queue->count - 1; ++i)
    queue->tasks[i] = queue->tasks[i + 1];
  --queue->count;
  pthread_mutex_unlock(&queue->mutex);
  return task;
}
