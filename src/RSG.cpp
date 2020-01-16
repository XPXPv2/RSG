#include "RSG.hpp"

using namespace std;

mutex MUX;

void printList(list<string> vlist, string sep){
  list<string> :: iterator itr;
  for ( itr = vlist.begin(); itr != vlist.end(); itr++){
    cout << (*itr) << sep;
  }
  cout << endl;
}

ThreadHandler::ThreadHandler(){
  this->total = 0;
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

stringGen::stringGen(){
  srand(time(NULL));
  return;
}
stringGen::~stringGen(){
  delete [] this->charSet;
  return;
}
int stringGen::returnList(list<string> *copyLoc){
  unordered_set<string> :: iterator itr;
  for ( itr = (this->strings).begin(); itr != (this->strings).end(); itr++){
    copyLoc->push_back(*itr);
  }
  return 0;
}
int stringGen::returnListLen(){
  return this->strings.size();
}

int stringGen::addString(string toAdd){
  if((this->strings).find(toAdd) != (this->strings).end()){
    return -1;
  }
  (this->strings).insert(toAdd);
  return 0;
}

int stringGen::setCharSet(char cset[],int len){
  delete [] this->charSet;
  this->setLen = len;
  this->charSet = new char [len];
  for(int i =0; i < len; i++){
    (this->charSet)[i] = cset[i];
  }
  return 0;
}

//TODO rework to be more random tempatry
int stringGen::randIndex(){
  return rand() % (this->setLen);
}

string stringGen::genString(int len){
  string prd;
  for(int i = 0; i < len; i++){
    prd += (this->charSet)[(this->randIndex())];
  }
  return prd;
}

int stringGen::genStrings(int number, int len){
  int max = pow((this->setLen), len);
  cout << max;
  if (number > max){
    return -1;
  }
  string str;
  for(int i = 0;i < number;i++){
    str = this->genString(len);
    MUX.lock();
    if(this->addString(str) == -1){
      MUX.unlock();
      i--;
      cout << "retry";
      continue;
    } else {
      MUX.unlock();
    }
    //cout << "added " << str;
  }
  return 0;
}
