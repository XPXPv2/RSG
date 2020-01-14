#include "RSG.hpp"

//decloration of the mutex
std::mutex MUX;


// functions to add

stringGen::stringGen(){
  //initalizes the nessary things for randomness
  this->initRandom();
  return;
}
stringGen::~stringGen(){
  this->clearMemory();
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
//int stringGen::returnListLen();

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
  std::string temp;
  for(int i = 0; i < len; i++){
    temp += (this->charSet)[(this->randIndex())];
  }
  return temp;
}

//gernerates strings and adds them to the list
//int stringGen::genStrings(int number);

//starts threads equal to (threadNumber) running genStrings
//int stringGen::startStringThread(int threadNumber, int stringNumber);

//divys up the number strings to be generated to the threads it starts with startStringThread
//int stringGen::stringThreadHandler(int threadNumber, int stringNumber);

//frees up any allocated memory
int stringGen::clearMemory(){
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
