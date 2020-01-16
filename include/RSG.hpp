#include <fstream>
#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include <mutex>
#include <list>
#include <unordered_set>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;


void printList(list<string> vlist,string sep);

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

class stringGen{
public:
  stringGen();
  ~stringGen();
  int setCharSet(char cset[],int len);
  int returnList(list<string> *copyLoc);
  int returnListLen();
  int addString(string toAdd);
  int genStrings(int number, int len);
private:
  string genString(int len);
  int randIndex();
  unordered_set <string> strings;
  char *charSet = NULL;
  int total, setLen = 0;
};
