#ifndef	__THREAD_H__
#define __THREAD_H__

#include <pthread.h>
#include <sys/types.h>
#include <unistd.h> 
#include <sys/syscall.h>
#include <errno.h>
#include <sched.h>
#ifdef	__cplusplus
extern "C" {
#endif

typedef void* (*THREAD_PROC)(void*);

#ifdef	__cplusplus
}
#endif


typedef pthread_t			thread_t;

#define thread_yield		sched_yield
#define thread_getid	  syscall(SYS_gettid)	
#define thread_create		pthread_create
#define thread_join			pthread_join

#endif
