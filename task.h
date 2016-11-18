#ifndef __TASK_H_
#define __TASK_H_
#include "pthread.h"
struct task
{
	char name[20];
	pthread_t id;
	void *(*func)(void *arg);
};

int TaskCreat(struct task *ptask, const char *name, void *funcname(void *arg));
#endif
