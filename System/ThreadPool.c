#include "ThreadPool.h"

#include <stdlib.h>

void* thread_job(void* arg);
void* add_work(struct ThreadPool* thread_pool, struct ThreadJob job);


struct ThreadPool thread_pool_constructor(int num_threads)
{
	struct ThreadPool thread_pool;
	thread_pool.num_threads = num_threads;
	thread_pool.active = 1;
	thread_pool.pool = (HANDLE*)malloc(sizeof(HANDLE[num_threads]));
	for (int i = 0; i < num_threads; i++)
	{
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) thread_job, NULL, 0, (LPDWORD) &thread_pool.pool[i]);
	}
	thread_pool.work = queue_constructor();
	thread_pool.add_work = add_work;
	InitializeCriticalSection(&thread_pool.lock);
	InitializeConditionVariable(&thread_pool.signal);
	return thread_pool;

}

void thread_pool_destructor(struct ThreadPool* thread_pool)
{
	thread_pool->active = 0;
	for (int i = 0; i < thread_pool->num_threads; i++)
	{
		WakeConditionVariable(&thread_pool->signal);
	}
	for (int i = 0; i < thread_pool->num_threads; i++)
	{
		WaitForSingleObject(&thread_pool->pool[i], 0);
	}
	free(&thread_pool->pool);
	queue_destructor(&thread_pool->work);
}

struct ThreadJob thread_job_constructor(void* (*job_function)(void* arg), void* arg)
{
	struct ThreadJob thread_job;
	thread_job.arg = arg;
	thread_job.job = job_function;
	return thread_job;
}

void* thread_job(void* arg)
{
	struct ThreadPool* thread_pool = (struct ThreadPool*)arg;
	while (thread_pool->active == 1)
	{
		EnterCriticalSection(&thread_pool->lock);
		SleepConditionVariableCS(&thread_pool->signal, &thread_pool->lock, 0);
		struct ThreadJob* job = (struct ThreadJob*) thread_pool->work.peek(&thread_pool->work);
		thread_pool->work.pop(&thread_pool->work);
		LeaveCriticalSection(&thread_pool->lock);
		if (job->job)
		{
			job->job(job->arg);
		}
	}
	return NULL;
}

void* add_work(struct ThreadPool* thread_pool, struct ThreadJob job)
{
	thread_pool->work.push(&job, sizeof(job), &thread_pool->work);
}