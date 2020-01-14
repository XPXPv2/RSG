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
  stringGen gen(5); // create object currently disabled due to lack of implumentation
  cout << "testing set setting" << endl;
  //test setting set with string
  gen.setCharSet(TESTSTRINGSET);
  cout << "finsished set setting" << endl;
  cout << "testing string adding and retrval" << endl;
  cout << "adding string" << endl;
  gen.addString("abc");
  cout << "reteaved: "<< endl;
  printList(gen.returnList(),", ");
  cout << "testing removeal" << endl;
  gen.clearMemory(true,true,false);
  cout << "reteaved: "<< endl;
  printList(gen.returnList(),", ");
  cout << "finsished testing sting storage" << endl;
  cout << "testing string generation" << endl;
  cout << "generated: " << gen.genString(10) << endl;
  cout << "finsished testing sting gen" << endl;
  cout << "testing multable string generation" << endl;
  gen.genStrings(10);
  cout << "generated: "<< endl;
  printList(gen.returnList(),", ");
  gen.clearMemory(false,true,true);
  list<char> a = TESTLISTSET;
  gen.setCharSet(a);
  cout << "finished testing multable string gen"<< endl;
  cout << "testing multithreaded string gen"<< endl;
  cout << "starting 10 threads 2 strings each"<< endl;
  gen.startStringThread(10,2);
  gen.clearMemory(true,false,false);
  cout << "generated: "<< endl;
  printList(gen.returnList(),", ");
  cout << "with length: " << gen.returnListLen() << endl;
  cout << "finished testing multithreaded string gen" << endl;

  cout << "testing full multithreading 5 threads 101 strings" << endl;
  gen.clearMemory(true,true,false);
  gen.stringThreadHandler(5,101);
  gen.clearMemory(true,false,false);
  cout << "generated: "<< endl;
  printList(gen.returnList(),", ");
  cout << "with length: " << gen.returnListLen() << endl;
  cout << "finished testing full multithreading 5 threads 101 strings" << endl;
  
  return;
}

void printList(list<string> vlist, string sep){
  list<string> :: iterator itr;
  for ( itr = vlist.begin(); itr != vlist.end(); itr++){
    cout << (*itr) << sep;
  }
  cout << endl;
}
