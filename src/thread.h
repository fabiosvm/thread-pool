//
// thread.h
//

#ifndef THREAD_H
#define THREAD_H

#ifdef _WIN32
  #include <windows.h>
#else
  #include <pthread.h>
#endif

#ifdef _WIN32
  #define thread_t       HANDLE
  #define thread_mutex_t CRITICAL_SECTION
  #define thread_cond_t  CONDITION_VARIABLE
#else
  #define thread_t       pthread_t
  #define thread_mutex_t pthread_mutex_t
  #define thread_cond_t  pthread_cond_t
#endif

int thread_create(thread_t *th, void *(*handler)(void *), void *arg);
int thread_join(thread_t th);
int thread_mutex_init(thread_mutex_t *mutex);
int thread_mutex_destroy(thread_mutex_t *mutex);
int thread_mutex_lock(thread_mutex_t *mutex);
int thread_mutex_unlock(thread_mutex_t *mutex);
int thread_cond_init(thread_cond_t *cond);
int thread_cond_destroy(thread_cond_t *cond);
int thread_cond_wait(thread_cond_t *cond, thread_mutex_t *mutex);
int thread_cond_signal(thread_cond_t *cond);

#endif // THREAD_H
