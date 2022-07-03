//
// main.c
//

#include <stdlib.h>
#include <stdio.h>
#include "thread_pool.h"

static void task_handler(void *ctx);

static void task_handler(void *ctx)
{
  long i = (long) ctx;
  printf("task %ld done!\n", i);
}

int main(int argc, char *argv[])
{
  int size = argc > 1 ? atoi(argv[1]) : 0;
  size = size ? size : THREAD_POOL_DEFAULT_SIZE;

  thread_pool_t pool;
  thread_pool_init(&pool, size);

  for (int i = 0; i < 100; ++i)
    thread_pool_submit_task(&pool, task_new((void *) ((long) i), &task_handler));

  thread_pool_free(&pool);
  return EXIT_SUCCESS;
}
