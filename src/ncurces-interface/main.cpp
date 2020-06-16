#include "gui.hpp"

int main(int argc, char const *argv[]) {
  ncursesGui program;
  program.init();
  program.mainLoop();
  program.exit();
  return 0;
}
