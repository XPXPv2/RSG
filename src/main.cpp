#include "RSG.hpp"
using namespace std;

void testThread(int name){
  printf("Thread %d Start\n",name );
  this_thread::sleep_for (std::chrono::seconds(name));
  printf("Thread %d Finish\n",name );
  return;
}

int main(int argc, char const *argv[]) {
  ThreadHandler test;
  for(int a =0;a < 1; a++){
    test.addThread(1,testThread,a);
  }

  test.Finish();
  stringGen test2;
  char a[] = {'a','b','c'};
  list<string> b;
  test2.setCharSet(a,3);
  test2.genStrings(81,4);
  test2.returnList(&b);
  cout << "returned List: " << b.size() << " internal list: " << test2.returnListLen() << endl;
  printList(b, " : ");
  cout << endl << "done tesing";
  return 0;
}
