#include "RSG.hpp"
using namespace std;

//deuging puposes remove for final relase
#define TESTSTRINGSET "ABCDEFG"
#define TESTLISTSET {'a','b','c','d','e','f','g'}


void printList(list<string> vlist, string sep);
void testRSG();

int main(int argc, char const *argv[]) {
  cout << "testing RSG" << endl;
  testRSG();
  cout << "finished testing RSG" << endl;
  return 0;
}

void testRSG(){
  cout << "starting object" << endl;
  //stringGen gen; // create object currently disabled due to lack of implumentation
  cout << "testing set setting" << endl;
  //test setting set with string
  //gen.setCharSet(TESTSTRINGSET); //currently disabled due to lack of implumentation
  //test setting with list
  //gen.setCharSet(TESTLISTSET); //currently disabled due to lack of implumentation
  cout << "finsished set setting" << endl;
  return;
}

void printList(list<string> vlist, string sep){
  list<string> :: iterator itr;
  for ( itr = vlist.begin(); itr != vlist.end(); itr++){
    cout << (*itr) << sep;
  }
  cout << endl;
}
