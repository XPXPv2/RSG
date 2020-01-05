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
  for(int a =0;a < 100; a++){
    test.addThread(1,testThread,a);
  }

  test.Finish();
  cout << endl << "dont tesing";
  return 0;
}
