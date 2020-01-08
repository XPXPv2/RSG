#include "RSG.hpp"

//decloration of the mutex
std::mutex MUX;


// functions to add

stringGen::stringGen(){
  //initalizes the nessary things for randomness
  this->initRandom();
  return;
}
//stringGen::~stringGen();
// set the Set
//int stringGen::setCharSet(std::string set);
//int stringGen::setCharSet(std::list<char> set);

// returns list of strings
//int stringGen::returnList(std::list<std::string> *copyLoc);
//std::list<std::string> stringGen::returnList();

//returns number of strings
//int stringGen::returnListLen();

// adds string to string list
//int stringGen::addString(std::string toAdd);

//gernerates a single string of lengh (len)
//std::string stringGen::genString(int len);

//gernerates strings and adds them to the list
//int stringGen::genStrings(int number);

//starts threads equal to (threadNumber) running genStrings
//int stringGen::startStringThread(int threadNumber, int stringNumber);

//divys up the number strings to be generated to the threads it starts with startStringThread
//int stringGen::stringThreadHandler(int threadNumber, int stringNumber);

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
