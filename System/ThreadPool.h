#ifndef ThreadPool_h
#define ThreadPool_h

#include <Windows.h>
#include "../DataStructures/Lists/Queue.h"

struct ThreadJob
{
	void* (*job)(void* arg);
	void* arg;
};

struct ThreadPool
{
	int num_threads;
	int active;
	struct Queue work;
	HANDLE* pool;
	CRITICAL_SECTION lock;
	CONDITION_VARIABLE signal;

	void* (*add_work)(struct ThreadPool* thread_pool, struct ThreadJob job);

};



struct ThreadPool thread_pool_constructor(int num_threads);
struct ThreadJob thread_job_constructor(void* (*job_function)(void* arg), void* arg);

void thread_pool_destructor(struct ThreadPool* thread_pool);

#endif