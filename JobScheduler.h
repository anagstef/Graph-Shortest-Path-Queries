#ifndef JOBSCHEDULER_H
#define JOBSCHEDULER_H

#include <pthread.h>
#include "worker_routine.h"
#include "Queue_.h"
#include "Job.h"

#define JS_QUEUE_INIT_SIZE 900000
#define JS_RESULTS_INIT_SIZE 900000

// #define JOBS_PER_THREAD 500

class JobScheduler;

struct thread_info{
  JobScheduler* js;
  int threadID;
};

class JobScheduler{
private:
  int execution_threads;
  pthread_t* threads;
  thread_info* info;

  Queue<Job*> JobQueue{JS_QUEUE_INIT_SIZE};
  int* results;
  uint32_t resultsSize;
  uint32_t resultsLeft;
  uint32_t resultsDone;
  uint32_t resultsToPrint;
  uint32_t priorityNum;
  // pthread_mutex_t mtx;
  // pthread_cond_t master, worker;

public:
  pthread_mutex_t mtx;
  pthread_cond_t master, worker;

  JobScheduler(int threadsNum);
  ~JobScheduler();

  void submit_job(Job* j);
  void execute_all_jobs();
  void wait_all_tasks_finish();
  // void* worker_routine(void* arg);
  uint32_t getResultsLeft(){return resultsLeft;}
  int getJobs(Job** jobsArray, uint32_t n);
  void setResults(Job** jobsArray, uint32_t n);
  void printResults();
};

#endif
