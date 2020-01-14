#include "RSG.hpp"

//decloration of the mutex
std::mutex MUX;


// functions to add

stringGen::stringGen(int stringLen){
  //initalizes the nessary things for randomness
  this->initRandom();
  this->stringLen = stringLen;
  return;
}
stringGen::~stringGen(){
  this->clearMemory(true,true,true);
  return;
}
// set the Set
int stringGen::setCharSet(std::string set){
  this->charSet = set;
  this->setLen = this->charSet.length();
  return 0;
}
int stringGen::setCharSet(std::list<char> set){
  std::string temp;
  std::list<char>::iterator itor;
  for(itor = set.begin();itor != set.end(); itor++){
    temp += *itor;
  }
  this->charSet = temp;
  this->setLen = this->charSet.length();
  return 0;
}

// returns list of strings
//int stringGen::returnList(std::list<std::string> *copyLoc);
std::list<std::string> stringGen::returnList(){
  std::list<std::string> temp;
  temp.insert(temp.end(),this->strings.begin(),this->strings.end());
  return temp;
}

//returns number of strings
int stringGen::returnListLen(){
  return this->strings.size();
}

// adds string to string list
int stringGen::addString(std::string toAdd){
  if((this->strings).find(toAdd) != (this->strings).end()){
    return -1;
  }
  (this->strings).insert(toAdd);
  return 0;
}

//gernerates a single string of lengh (len)
std::string stringGen::genString(int len){
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
int stringGen::genStrings(int number){
  int max = pow((this->setLen), this->stringLen);
  if (number > max){
    return -1;
  }
  std::string temp;
  for(int i = 0;i < number;i++){
    temp = this->genString(this->stringLen);
    if(temp == ""){
      return -1;
    }
    MUX.lock();
    if(this->addString(temp) == -1){
      MUX.unlock();
      i--;
      continue;
    } else {
      MUX.unlock();
    }
    //cout << "added " << str;
  }
  return 0;
}

//starts threads equal to (threadNumber) running genStrings
int stringGen::startStringThread(int threadNumber, int stringNumber){
  std::thread *threadPTR = NULL;
  for(int i = 0;i < threadNumber;i++){
    threadPTR = new std::thread(&stringGen::genStrings,this,stringNumber);
    this->threadList.push_back(threadPTR);
    this->threadCount++;
  }
  return 0;
}

//divys up the number strings to be generated to the threads it starts with startStringThread
//int stringGen::stringThreadHandler(int threadNumber, int stringNumber);

//frees up any allocated memory
int stringGen::clearMemory(bool threads,bool list,bool set){
  if(list){
    this->strings.erase(this->strings.begin(), this->strings.end());
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
  }
  return 0;
}


// rework the following two functions
//selects random index of the Set
int stringGen::randIndex(){
  return rand() % (this->setLen);
}

//initalizes the randomizer
int stringGen::initRandom(){
  srand(time(NULL));
  return 0;
}
