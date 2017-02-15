#include "JobScheduler.h"

using namespace std;

//initialize jobscheduler
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

//master thread submits a job
void JobScheduler::submit_job(Job* j){
  j->setPriority(priorityNum);
  priorityNum++;
  JobQueue.push(j);
}

//master thread signals all worker threads to begin executing
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

//waiting for worker threads to finish
void JobScheduler::wait_all_tasks_finish(){

  while(resultsLeft > 0){
    pthread_cond_wait(&master, &mtx);
  }
  priorityNum = 0;
  JobQueue.clear();
}

//worker thread is getting a number of jobs to execute
int JobScheduler::getJobs(Job** jobsArray, uint32_t n){
  if(resultsLeft < n)
    n = resultsLeft;

  for(uint32_t i=0; i<n; i++){
    jobsArray[i] = JobQueue.pop();
  }

  resultsLeft -= n;
  return n;
}

//setting results to results array
void JobScheduler::setResults(Job** jobsArray, uint32_t n){
  for(uint32_t i=0; i<n; i++){
    results[jobsArray[i]->getPriority()] = jobsArray[i]->getResult();
  }
  pthread_mutex_lock(&mtx);

  resultsDone += n;
  if(resultsDone == resultsToPrint)
    pthread_cond_signal(&master);

  pthread_mutex_unlock(&mtx);
}

//printing the whole array with the results
void JobScheduler::printResults(){
  for(uint32_t i=0; i<resultsToPrint; i++){
    printf("%d\n", results[i]);
  }
}

//exiting threads
void JobScheduler::exitThreads(){
  exitflag = true;
  pthread_mutex_unlock(&mtx);
  pthread_cond_broadcast(&worker);
  // std::cerr << "exiting..." << std::endl;
  for(int i=0;i<execution_threads; i++)
    pthread_join(threads[i], NULL);
  pthread_mutex_lock(&mtx);
}
