#include "gui.hpp"

int main() {
  ncursesGui program;
  program.init();
  program.mainLoop();
  program.exit();
  return 0;
}
