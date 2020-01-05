#include <fstream>
#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include <mutex>
#include <list>

using namespace std;


class ThreadHandler{
public:
  ThreadHandler();
  ~ThreadHandler();
  int Finish();

  template <class parm,class fun>
  int addThread(int number,fun func,parm paramiter){
    for(int Tnum =0; Tnum < number;Tnum++){
      thread *threadPTR = new thread(func,paramiter);
      this->threadList.push_back(threadPTR);
      this->total++;
    }
    return 0;
  }



private:
  int total;
  list<thread*> threadList;
};
