
#ifndef _SPINLOCK_H_
#define _SPINLOCK_H_

#include "atomic.h"
#include "thread.h"

#ifdef	__cplusplus
extern "C" {
#endif

static inline void 
spin_lock(volatile int *lock)
{
	int l;
	int i = 10;
	int id = thread_getid;
	for (l=atomic_comp_swap(lock, id, 0);
		l!=0 && l!=id; 
		l=atomic_comp_swap(lock, id, 0)
	) {
		if (i --) { 
			nop(); 
		} 
		else { 
			i = 10; 
			thread_yield();
		}
	}
}

static inline bool
spin_unlock(volatile int *lock)
{
	int id = thread_getid;
	return id == atomic_comp_swap(lock, 0, id);
}

static inline bool 
spin_trylock(volatile int *lock)
{
	int id = thread_getid;
	int owner = atomic_comp_swap(lock, id, 0);
	return (owner==0 || owner==id);
}

static inline int
token_acquire(volatile int *token, int id)
{
	return atomic_comp_swap(token, id, 0);
}

static inline int
token_release(volatile int *token, int id)
{
	return atomic_comp_swap(token, 0, id);
}

static inline int
token_transfer(volatile int *token, int oldid, int newid)
{
	return atomic_comp_swap(token, newid, oldid);
}

static inline int
token_set(volatile int *token, int id)
{
    return atomic_comp_swap(token, id, *token);
}

#ifdef	__cplusplus
}
#endif

#endif
