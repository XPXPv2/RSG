#include "RSG.hpp"

using namespace std;


ThreadHandler::ThreadHandler(){
  this->total = 0;
  //*threadList = new thread{3};
  //cout << this->threadList.size();
  return;
}

int ThreadHandler::Finish(){
  if (this->total <1){
    return 0;
  }
  for(auto const& i : this->threadList){
    if(i->joinable()){
      i->join();
    }
    delete i;
    this->total--;
  }
  list<thread*> (this->threadList);
  return 0;
}

ThreadHandler::~ThreadHandler(){
  this->Finish();
  return;
}
