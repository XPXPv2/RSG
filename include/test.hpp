#define CATCH_CONFIG_RUNNER
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "catch.hpp"
#include "RSG.hpp"

#include <algorithm>

using namespace std;



int RSGtest(int argc, char const *argv[]){

  int result = Catch::Session().run( argc, argv );
  return result;

}

TEST_CASE("RSG gen"){
  stringGen generator(5);

  SECTION("Setting char set via string"){
    REQUIRE(generator.setCharSet("abc") == 0);
    REQUIRE(generator.returnSet() == "abc");
  }
  SECTION("Setting char set via list"){
    list<char> Cset = {'A','B','C'};
    REQUIRE(generator.setCharSet(Cset) == 0);
    REQUIRE(generator.returnSet() == "ABC");
  }
  SECTION("Setting and Retreving Strings"){
    REQUIRE(generator.addString("abc") == 0);
    REQUIRE(generator.returnList().front() == "abc");
  }
  SECTION("Testing Removal of Strings and Sets"){
    REQUIRE(generator.clearMemory(true,true,true) == 0);
    REQUIRE(generator.returnListLen() == 0);
    REQUIRE(generator.returnSet().size() == 0);
  }
  SECTION("Testing String Gen"){
    REQUIRE(generator.setCharSet("abc") == 0);
    REQUIRE(generator.genString(5).size() == 5);
  }
  SECTION("Testing String Generation"){
    REQUIRE(generator.genStrings(10) == 0);
    list<string> strings = generator.returnList();
    strings.sort();
    REQUIRE(unique(strings.begin(),strings.end()) == strings.end());
  }
}
