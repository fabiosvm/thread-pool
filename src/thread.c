//
// thread.c
//

#include "thread.h"

int thread_create(thread_t *th, void *(*handler)(void *), void *arg)
{
#ifdef _WIN32
  *th = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) handler, arg, 0, NULL);
  return !(*th) ? -1 : 0;
#else
  return pthread_create(th, NULL, handler, arg);
#endif
}

int thread_join(thread_t th)
{
#ifdef _WIN32
  return WaitForSingleObject(th, INFINITE) == WAIT_OBJECT_0;
#else
  return pthread_join(th, NULL);
#endif
}

int thread_mutex_init(thread_mutex_t *mutex)
{
#ifdef _WIN32
  InitializeCriticalSection(mutex);
  return 0;
#else
  return pthread_mutex_init(mutex, NULL);
#endif
}

int thread_mutex_destroy(thread_mutex_t *mutex)
{
#ifdef _WIN32
  DeleteCriticalSection(mutex);
  return 0;
#else
  return pthread_mutex_destroy(mutex);
#endif
}

int thread_mutex_lock(thread_mutex_t *mutex)
{
#ifdef _WIN32
  EnterCriticalSection(mutex);
  return 0;
#else
  return pthread_mutex_lock(mutex);
#endif
}

int thread_mutex_unlock(thread_mutex_t *mutex)
{
#ifdef _WIN32
  LeaveCriticalSection(mutex);
  return 0;
#else
  return pthread_mutex_unlock(mutex);
#endif
}

int thread_cond_init(thread_cond_t *cond)
{
#ifdef _WIN32
  InitializeConditionVariable(cond);
  return 0;
#else
  return pthread_cond_init(cond, NULL);
#endif
}

int thread_cond_destroy(thread_cond_t *cond)
{
#ifdef _WIN32
  return 0;
#else
  return pthread_cond_destroy(cond);
#endif
}

int thread_cond_wait(thread_cond_t *cond, thread_mutex_t *mutex)
{
#ifdef _WIN32
  return SleepConditionVariableCS(cond, mutex, INFINITE);
#else
  return pthread_cond_wait(cond, mutex);
#endif
}

int thread_cond_signal(thread_cond_t *cond)
{
#ifdef _WIN32
  WakeConditionVariable(cond);
  return 0;
#else
  return pthread_cond_signal(cond);
#endif
}
