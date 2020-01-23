

#ifndef TEST
#define TEST 0
#include "RSG.hpp"
#else
#undef TEST
#define TEST 1
#include "test.hpp"
#endif

#include <iostream>
using namespace std;

void printList(list<string> vlist, string sep);

// input args are NUMBEROS NUMBEROT LENGTHOS SET

int main(int argc, char const *argv[]) {
  #if TEST == 1
  return RSGtest(argc,argv);
  #endif
  if(argc < 4){
    cout << "You did not supply engouh arguments" << endl;
    return -1;
  }
  int NoS , NoT, LoS;
  string set;
  NoS = strtol(argv[1],nullptr,0);
  NoT = strtol(argv[2],nullptr,0);
  LoS = strtol(argv[3],nullptr,0);
  set = argv[4];
  stringGen gen(LoS);
  gen.setCharSet(set);
  gen.stringThreadHandler(NoT,NoS);
  gen.clearMemory(true,false,false);
  //printList(gen.returnList()," ,");
  return 0;
}

void printList(list<string> vlist, string sep){
  list<string> :: iterator itr;
  for ( itr = vlist.begin(); itr != vlist.end(); itr++){
    cout << (*itr) << sep;
  }
  cout << endl;
}
