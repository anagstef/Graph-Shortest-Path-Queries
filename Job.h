#ifndef JOB_H
#define JOB_H

class Job{
protected:
  uint32_t priority;
  int result;
public:
  virtual ~Job(){}
  virtual void execute(int threadID)=0;
  int getResult(){return result;}
  void setPriority(uint32_t p){priority=p;}
  uint32_t getPriority(){return priority;}
};

#endif
