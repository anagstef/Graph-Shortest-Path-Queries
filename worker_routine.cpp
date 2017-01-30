#include <pthread.h>
#include "JobScheduler.h"
#include "Job.h"

using namespace std;

void* worker_routine(void* arg){
  Job* jobs[JOBS_PER_THREAD];
  thread_info* info = (thread_info*) arg;
  JobScheduler* js = info->js;
  int threadID = info->threadID;

  while(1){

    //lock mutex
    pthread_mutex_lock(&(js->mtx));

    //if queue is empty then block on cond var
    while(js->getResultsLeft() == 0){
      pthread_cond_wait(&(js->worker), &(js->mtx));
    }

    //get JOBS_PER_THREAD or less (n) jobs from the queue
    uint32_t n = js->getJobs(jobs, JOBS_PER_THREAD);

    //unlock mutex
    pthread_mutex_unlock(&(js->mtx));

    //execute all jobs
    for(uint32_t i=0; i<n; i++){
      jobs[i]->execute(threadID);
    }

    //give results to JobScheduler
    js->setResults(jobs, n);

  }

}
