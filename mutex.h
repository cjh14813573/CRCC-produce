#ifndef __MUTEX_H_
#define __MUTEX_H_
#include <sys/types.h>
typedef pthread_mutex_t MUTEX_T;
int MutexUnlock(void* mutex);
int MutexLock(void* mutex);
int MutexCreat(void* mutex);
int MutexTrylock(void* mutex);
int MutexDestroy(void* mutex);

#endif //__MUTEX_H_
