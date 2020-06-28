

#include <thread>
#include <string>
#include <mutex>
#include <list>
#include <unordered_set>
#include <cmath>


namespace rsg{

class stringGen{
public:
  stringGen();
  ~stringGen();
  //test if the the request amout of strings is posable
  int possibleGen(int number);
  // set the Set
  int setCharSet(std::string set);
  int setCharSet(std::list<char> set);

  int setStringLength(int number);
  int returnStringLength();

  std::string returnSet();

  // returns list of strings
  int returnList(std::list<std::string> *copyLoc);
  std::list<std::string> returnList();

  //returns number of strings
  int returnListLen();

  //clears threads list or set or all
  int clearMemory(bool threads,bool list,bool set);

  //terminates threads
  int terminateThreads();

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
  int setLen = 0;
  int threadCount = 0;
  int stringLen = 0;
  bool runThreads = true;

  //declaration of the mutex
  std::mutex mutex;

  //functions
  int randIndex();
  int initRandom();

};


}
