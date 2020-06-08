

#ifdef NDEBUG
#define TEST 0
#include "gui.hpp"
#else
#define TEST 1
#include "test.hpp"
#endif


#include <iostream>
#include <fstream>
using namespace std;

void printList(list<string> vlist, string sep);
void writeList(list<string> vlist,string name);

// input args are NUMBEROS NUMBEROT LENGTHOS SET SAVEFILE

int main(int argc, char const *argv[]) {
  #if TEST == 1
  return RSGtest(argc,argv);
  #endif

  ncursesGui program;
  program.init();
  program.mainLoop();
  program.exit();
  return 0;

}

void printList(list<string> vlist, string sep){
  list<string> :: iterator itr;
  for ( itr = vlist.begin(); itr != vlist.end(); itr++){
    cout << (*itr) << sep;
  }
  cout << endl;
}
void writeList(list<string> vlist,string name){
  ofstream file;
  file.open(name);
  list<string> :: iterator itr;
  for ( itr = vlist.begin(); itr != vlist.end(); itr++){
    file << (*itr) << endl;
  }
  file.close();
}
