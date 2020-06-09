

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

<<<<<<< ours
  ncursesGui program;
  program.init();
  program.mainLoop();
  program.exit();
=======
  rsg::stringGen gen;
  gen.setStringLength(LoS);
  gen.setCharSet(set);
  if (gen.stringThreadHandler(NoT,NoS) == -1){
    cout << "error" << endl;
    gen.clearMemory(true,true,true);
    return -1;
  }
  gen.clearMemory(true,false,false);
  cout << "Size of strings (bytes): " << (sizeof(list<string>) + (sizeof(string) * gen.returnListLen())) << endl;
  //printList(gen.returnList()," ,");
  if (save != ""){
    writeList(gen.returnList(),save);
  }
>>>>>>> theirs
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
    file << (*itr) << '\n';
  }
  file.close();
}
