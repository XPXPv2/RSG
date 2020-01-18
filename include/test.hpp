#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "RSG.hpp"

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
}
