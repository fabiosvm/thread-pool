//
// thread_pool.c
//

#include "thread_pool.h"
#include <stdlib.h>
#include <assert.h>

static void *thread_handler(void *arg);

static void *thread_handler(void *arg)
{
  task_queue_t *queue = (task_queue_t *) arg;
  for (;;)
  {
    task_t task = task_queue_dequeue(queue);
    task.handler(task.ctx);
  }
  return NULL;
}

void thread_pool_init(thread_pool_t *pool, int size)
{
  task_queue_init(&pool->queue);
  pool->size = size;
  pool->threads = malloc(sizeof(*pool->threads) * size);
  assert(pool->threads);
  for (int i = 0; i < pool->size; ++i)
    assert(!thread_create(&pool->threads[i], &thread_handler, &pool->queue));
}

void thread_pool_free(thread_pool_t *pool)
{
  for (int i = 0; i < pool->size; ++i)
    assert(!thread_join(pool->threads[i]));
  free(pool->threads);
  task_queue_free(&pool->queue);
}

void thread_pool_submit_task(thread_pool_t *pool, task_t task)
{
  task_queue_enqueue(&pool->queue, task);
}
