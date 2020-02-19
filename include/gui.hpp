#include <ncurses.h>

class ncursesGui{
public:
  ncursesGui();
  ~ncursesGui();

  int init();
  int exit();
  int mainLoop();
  int pollEvents();
  int draw();

private:
  bool allocated, active;
  int Xsize, Ysize;


};
