

#ifndef TEST
#define TEST 0
#include "RSG.hpp"
#else
#undef TEST
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
  if(argc < 6){
    cout << "You did not supply engouh arguments" << endl;
    return -1;
  }
  int NoS , NoT, LoS;
  string set, save;
  NoS = strtol(argv[1],nullptr,0);
  NoT = strtol(argv[2],nullptr,0);
  LoS = strtol(argv[3],nullptr,0);
  set = argv[4];
  save = argv[5];
  cout << "Aproximent needed RAM (bytes): " << (sizeof(list<string>) + (sizeof(string) * NoS)) << endl;

  stringGen gen(LoS);
  gen.setCharSet(set);
  if (gen.stringThreadHandler(NoT,NoS) == -1){
    cout << "error" << endl;
    gen.clearMemory(true,true,true);
    return -1;
  }
  gen.clearMemory(true,false,false);
  cout << "Size of strings (bytes): " << (sizeof(list<string>) + (sizeof(string) * gen.returnListLen())) << endl;
  //printList(gen.returnList()," ,");
  writeList(gen.returnList(),save);
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
