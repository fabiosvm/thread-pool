//
// thread_pool.h
//

#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include "task_queue.h"

#define THREAD_POOL_DEFAULT_SIZE (1 << 3)

typedef struct
{
  task_queue_t queue;
  int size;
  pthread_t *threads;
} thread_pool_t;

void thread_pool_init(thread_pool_t *pool, int size);
void thread_pool_free(thread_pool_t *pool);
void thread_pool_submit_task(thread_pool_t *pool, task_t task);

#endif // THREAD_POOL_H
