

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

int main(int argc, char const *argv[]) {
  #if TEST == 1
  return RSGtest(argc,argv);
  #endif
}
