#include "RSG.hpp"


rsg::stringGen::stringGen(){
  //initalizes the nessary things for randomness
  this->initRandom();
  return;
}
rsg::stringGen::~stringGen(){
  this->clearMemory(true,true,true);
  return;
}

int rsg::stringGen::posableGen(int number){
  if(pow(this->setLen,this->stringLen) < number) return -1;
  return 0;
}
// set the Set
int rsg::stringGen::setCharSet(std::string set){
  this->charSet = set;
  this->setLen = this->charSet.length();
  return 0;
}
int rsg::stringGen::setCharSet(std::list<char> set){
  std::string temp;
  std::list<char>::iterator itor;
  for(itor = set.begin();itor != set.end(); itor++){
    temp += *itor;
  }
  this->charSet = temp;
  this->setLen = this->charSet.length();
  return 0;
}

int rsg::stringGen::setStringLength(int stringLen){
  this->stringLen = stringLen;
  return 0;
}

int rsg::stringGen::returnStringLength(){
  return this->stringLen;
}

std::string rsg::stringGen::returnSet(){
  return this->charSet;
}

// returns list of strings
//int rsg::stringGen::returnList(std::list<std::string> *copyLoc);
std::list<std::string> rsg::stringGen::returnList(){
  std::list<std::string> temp;
  temp.insert(temp.end(),this->strings.begin(),this->strings.end());
  return temp;
}

//returns number of strings
int rsg::stringGen::returnListLen(){
  return this->strings.size();
}

// adds string to string list
int rsg::stringGen::addString(std::string toAdd){
  if((this->strings).find(toAdd) != (this->strings).end()){
    return -1;
  }
  (this->strings).insert(toAdd);
  return 0;
}

//gernerates a single string of lengh (len)
std::string rsg::stringGen::genString(int len){
  if(this->setLen == 0){
    return "";
  }
  std::string temp;
  for(int i = 0; i < len; i++){
    temp += (this->charSet)[(this->randIndex())];
  }
  return temp;
}

//gernerates strings and adds them to the list
int rsg::stringGen::genStrings(int number){
  if(this->posableGen(number) != 0) return -1;
  std::string temp;
  for(int i = 0;i < number && this->runThreads;i++){
    temp = this->genString(this->stringLen);
    if(temp == ""){
      return -1;
    }
    this->mutex.lock();
    if(this->addString(temp) == -1){
      this->mutex.unlock();
      i--;
      continue;
    } else {
      this->mutex.unlock();
    }
  }
  return 0;
}

//starts threads equal to (threadNumber) running genStrings
int rsg::stringGen::startStringThread(int threadNumber, int stringNumber){
  std::thread *threadPTR = NULL;
  for(int i = 0;i < threadNumber;i++){
    threadPTR = new std::thread(&rsg::stringGen::genStrings,this,stringNumber);
    this->threadList.push_back(threadPTR);
    this->threadCount++;
  }
  return 0;
}

//divys up the number strings to be generated to the threads it starts with startStringThread
int rsg::stringGen::stringThreadHandler(int threadNumber, int stringNumber){
  if(this->posableGen(stringNumber) != 0) return -1;

  int perThread = floor(stringNumber/threadNumber);
  int extra =  stringNumber % threadNumber;
  int tmp = (perThread + extra);
  this->startStringThread(1,tmp);
  this->startStringThread(threadNumber - 1, perThread);
  return 0;
}

//frees up any allocated memory
int rsg::stringGen::clearMemory(bool threads,bool list,bool set){
  if(list){
    this->strings.clear();
  }
  if(threads){
    for(auto const& i : this->threadList){
      if(i->joinable()){
        i->join();
      }
      delete i;
      this->threadCount--;
    }
    this->threadList.clear();
    this->runThreads = true;
  }
  if(set){
    this->setLen = 0;
    this->charSet.clear();
  }
  return 0;
}

int rsg::stringGen::terminateThreads(){
  this->runThreads = false;
  return 0;
}

// rework the following two functions
//selects random index of the Set
int rsg::stringGen::randIndex(){
  return rand() % (this->setLen);
}

//initalizes the randomizer
int rsg::stringGen::initRandom(){
  srand(time(NULL));
  return 0;
}
