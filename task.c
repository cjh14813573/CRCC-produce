#include "task.h"
#include "stdsys.h"
int TaskCreat(struct task *ptask, const char *name, void *funcname(void *arg))
{
	if(strlen(name) > sizeof(ptask->name)) return 1;
	strcpy((ptask->name), name);
	if(funcname == NULL) return 1;
	ptask->func = funcname;
	return pthread_create(&(ptask->id), NULL, (ptask->func), NULL);
}
