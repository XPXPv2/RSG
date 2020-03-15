#include <ncurses.h>

#ifndef NDEFALT
#define NDEFALT

#define ENTRYWINWITHRATIO .5
#define ENTRYWINHIGHTRATIO .5

#define SETWINWITHRATIO .5
#define SETWINHIGHTRATIO .5

#define PROGRESSWINWITHRATIO 1
#define PROGRESSWINHIGHTRATIO .5

#endif

class ncursesGui{
public:
  ncursesGui();
  ~ncursesGui();

  int init();
  int exit();
  int mainLoop();
  int pollEvents();
  int draw();
  int redraw();

private:
  bool allocated, active;

  WINDOW *entryWin;
  WINDOW *setWin;
  WINDOW *progressWin;

  void initEntryWin();
  void initSetWin();
  void initProgressWin();


};
