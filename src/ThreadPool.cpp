//
// Saar Shtalryd 307838854 & Itay Oktan 203036512
//

#include "ThreadPool.h"
#include <unistd.h>
#include <iostream>
/**
 * startJobs - the main function of every thread in the pool.
 * @param arg - this thread pool as a void*
 * @return
 */
static void *startJobs(void *arg) {
	ThreadPool *pool = (ThreadPool *)arg;
	pool->doJobs();
	return NULL;
}
/**
 * doJobs- the function of every thread in the pool, executing jobs.
 */
void ThreadPool::doJobs() {
	while (!stop) {
		pthread_mutex_lock(&lock);
		if (!jobs_queue.empty()) {
			Job* job = jobs_queue.front();
			jobs_queue.pop();
			pthread_mutex_unlock(&lock);
			//run the task function
			job->execute();
			//update how many jobs done untill now
			pthread_mutex_lock(&counterLock);
			this->jobsCounter++;
			pthread_mutex_unlock(&counterLock);
		}
		else {
			pthread_mutex_unlock(&lock);
			sleep(1);
		}
	}
	pthread_exit(NULL);
}
/**
 * addJob- adding a given job to jobs queue.
 * @param job
 */
void ThreadPool::addJob(Job *job) {

	jobs_queue.push(job);
}
/**
 * Constructor. creating the threads.
 * @param threads_num
 * @return
 */
ThreadPool::ThreadPool(int threads_num) : threads_num(threads_num), stop(false) {
	jobsCounter =0;
	// TODO Auto-generated constructor stub
	threads = new pthread_t[threads_num];

	pthread_mutex_init(&lock, NULL);
	pthread_mutex_init(&counterLock, NULL);
	for (int i = 0; i < threads_num; i++) {
		pthread_create(threads + i, NULL, startJobs, this);
	}
}
/**
 * terminate - stop handling jobs, and wait for current to finish.
 */
void ThreadPool::terminate() {
	stop = true;
	//waiting for current jobs to be finished.
	for (int i = 0; i < threads_num; i++) {
		pthread_join(*(threads + i), NULL);
	}
}
/**
 * Destructor.
 */
ThreadPool::~ThreadPool() {
	// TODO Auto-generated destructor stub
	delete[] threads;
	pthread_mutex_destroy(&lock);
	pthread_mutex_destroy(&counterLock);
}
/**
 * isEmpty - return true if there are no more jobs.
 * @return
 */
bool ThreadPool::isEmpty() {
	return jobs_queue.size()==0;
}
/**
 * getter for jobsCounter member.
 * @return
 */
int ThreadPool::getJobsCounter() const {
	return jobsCounter;
}

