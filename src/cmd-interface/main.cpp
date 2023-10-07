#include "RSG.hpp"

#include <iostream>
#include <fstream>
using namespace std;

void printList(list<string> vlist, string sep);
void writeList(list<string> vlist,string name);

#define inputs "input args are NUMBEROS NUMBEROT LENGTHOS SET SAVEFILE"

int main(int argc, char const *argv[]) {
  cout << inputs << endl;
  int NoS , NoT, LoS;
  string set, save;
  if(argc < 5){
    cout << "You did not supply engouh arguments" << endl;
    return -1;
  } else if(argc == 6){
    save = argv[5];
  } else {
    save = "";
  }
  NoS = strtol(argv[1],nullptr,0);
  NoT = strtol(argv[2],nullptr,0);
  LoS = strtol(argv[3],nullptr,0);
  set = argv[4];
  cout << "Aproximent needed RAM (bytes): " << (sizeof(list<string>) + (sizeof(string) * NoS)) << endl;

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
