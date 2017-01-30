#include "JobScheduler.h"

using namespace std;

JobScheduler::JobScheduler(int threadsNum){
  if(threadsNum < 1)
    execution_threads = 1;
  else
    execution_threads = threadsNum;

  info = (thread_info*) malloc(sizeof(thread_info) * execution_threads);

  pthread_mutex_init(&mtx, NULL);
  pthread_cond_init(&master, NULL);
  pthread_cond_init(&worker, NULL);

  priorityNum = 0;
  resultsSize = JS_RESULTS_INIT_SIZE;
  results = (int*) malloc(sizeof(int) * resultsSize);

  threads = (pthread_t*) malloc(sizeof(pthread_t) * execution_threads);

  pthread_mutex_lock(&mtx);

  for(int i=0; i<execution_threads; i++){
    info[i].js = this;
    info[i].threadID = i;
    pthread_create(&(threads[i]), NULL, &worker_routine,(void*) &(info[i]));
  }
}


JobScheduler::~JobScheduler(){
  free(results);
  free(threads);
  free(info);
  pthread_mutex_unlock(&mtx);
  pthread_mutex_destroy(&mtx);
  pthread_cond_destroy(&master);
  pthread_cond_destroy(&worker);
}

void JobScheduler::submit_job(Job* j){
  j->setPriority(priorityNum);
  priorityNum++;
  JobQueue.push(j);
}

void JobScheduler::execute_all_jobs(){
  resultsLeft = JobQueue.getSize();
  resultsToPrint = resultsLeft;
  resultsDone = 0;
  if(resultsLeft > resultsSize){
    resultsSize = resultsLeft*2;
    results = (int*) realloc(results, sizeof(int) * resultsSize);
  }
  pthread_cond_broadcast(&worker);
}

void JobScheduler::wait_all_tasks_finish(){

  while(resultsLeft > 0){
    pthread_cond_wait(&master, &mtx);
  }
  priorityNum = 0;
  JobQueue.clear();
}

int JobScheduler::getJobs(Job** jobsArray, uint32_t n){
  if(resultsLeft < n)
    n = resultsLeft;

  for(uint32_t i=0; i<n; i++){
    jobsArray[i] = JobQueue.pop();
  }

  resultsLeft -= n;
  return n;
}

void JobScheduler::setResults(Job** jobsArray, uint32_t n){
  for(uint32_t i=0; i<n; i++){
    results[jobsArray[i]->getPriority()] = jobsArray[i]->getResult();
    // delete jobsArray[i];
  }
  pthread_mutex_lock(&mtx);

  resultsDone += n;
  if(resultsDone == resultsToPrint)
    pthread_cond_signal(&master);

  pthread_mutex_unlock(&mtx);
}

void JobScheduler::printResults(){
  for(uint32_t i=0; i<resultsToPrint; i++){
    printf("%d\n", results[i]);
  }
}

// void* JobScheduler::worker_routine(void* arg){
//   Job* jobs[JOBS_PER_THREAD];
//   thread_info* info = (thread_info*) arg;
//   // JobScheduler* js = info->js;
//   int threadID = info->threadID;
//
//   while(1){
//
//     //lock mutex
//     pthread_mutex_lock(&mtx);
//
//     //if queue is empty then block on cond var
//     while(getResultsLeft() == 0){
//       pthread_cond_wait(&worker, &mtx);
//     }
//
//     uint32_t n = getJobs(jobs, JOBS_PER_THREAD);
//
//     pthread_mutex_unlock(&mtx);
//
//     //execute all jobs
//     for(uint32_t i=0; i<n; i++){
//       jobs[i]->execute(threadID);
//     }
//
//
//     //give results to JobScheduler
//     setResults(jobs, n);
//
//
//   }
//
// }
