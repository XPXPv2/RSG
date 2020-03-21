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

#define ENTRYLABLES {"Number of Strings:","Length of Strings:","Number of Threads:","Save File:"}

#define STARTLABLE "Start:F1"
#define STOPLABLE "Stop:F2"

#endif

#define ERRORCOLOR 1
#define FINECOLOR 2

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

  int labelColors[7] = {FINECOLOR,FINECOLOR,FINECOLOR,FINECOLOR,FINECOLOR,FINECOLOR,ERRORCOLOR};

  WINDOW *entryWin = NULL;
  WINDOW *setWin = NULL;
  WINDOW *progressWin = NULL;
  WINDOW *progressBar = NULL;

  FIELD *setField[2];
  FORM *setForm;

  FIELD *entryField[5];
  FORM *entryForm;

  int progressBarWidth = 0, percentPosition = 0;

  void initEntryWin();
  void initSetWin();
  void initProgressWin();

  void initSetForm(int width,int hight);
  void initEntryForm(int width,int hight);

  void clearWindows();

  void setProgressBar(float percentage);
  void printLables(int colors[7]);


};
