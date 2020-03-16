#include <ncurses.h>
#include <form.h>
#include <string>

#ifndef NDEFALT
#define NDEFALT

#define ENTRYWINWITHRATIO .5
#define ENTRYWINHIGHTRATIO .5

#define SETWINWITHRATIO .5
#define SETWINHIGHTRATIO .5

#define PROGRESSWINWITHRATIO 1
#define PROGRESSWINHIGHTRATIO .5

#define PROGRESSBAROFFSET 2
#define PROGRESSBARCHAR '#'
#define PROGRESSBARENDCHAR '>'

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

  WINDOW *entryWin = NULL;
  WINDOW *setWin = NULL;
  WINDOW *progressWin = NULL;
  WINDOW *progressBar = NULL;

  int progressBarWidth = 0, percentPosition = 0;

  void initEntryWin();
  void initSetWin();
  void initProgressWin();

  void clearWindows();

  void setProgressBar(float percentage);


};
