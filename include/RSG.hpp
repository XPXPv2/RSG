#include <fstream>
#include <iostream>
#include <thread>
#include <string>
#include <mutex>
#include <list>
#include <unordered_set>
#include <cstdlib>
#include <ctime>

// posable need libarys


#include <cmath>
#include <algorithm>

class stringGen{
public:
  stringGen(int stringLen);
  ~stringGen();
  // set the Set
  int setCharSet(std::string set);
  int setCharSet(std::list<char> set);

  // returns list of strings
  int returnList(std::list<std::string> *copyLoc);
  std::list<std::string> returnList();

  //returns number of strings
  int returnListLen();

  //clears threads list or set or all
  int clearMemory(bool threads,bool list,bool set);

  // adds string to string list
  int addString(std::string toAdd);

  //gernerates a single string of lengh (len)
  std::string genString(int len);

  //gernerates strings and adds them to the list
  int genStrings(int number);

  //starts threads equal to (threadNumber) running genStrings
  int startStringThread(int threadNumber, int stringNumber);

  //divys up the number strings to be generated to the threads it starts with startStringThread
  int stringThreadHandler(int threadNumber, int stringNumber);

private:
  //vars
  std::unordered_set <std::string> strings;
  std::string charSet = "";
  std::list<std::thread*> threadList;
  int setLen, threadCount = 0;
  int stringLen = 0;

  //functions
  int randIndex();
  int initRandom();

};
