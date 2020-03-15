#include "gui.hpp"

ncursesGui::ncursesGui(){
  return;
}

ncursesGui::~ncursesGui(){

    this->exit();
}

int ncursesGui::init(){

    initscr();
    keypad(stdscr, TRUE);
    cbreak();

    this->allocated = true;

    return 0;
}

int ncursesGui::exit(){

  if(this->allocated){
    endwin();
    this->allocated = false;
  }

  return 0;
}

int ncursesGui::mainLoop(){

  this->active = true;

  refresh();
  this->draw();

  while(this->active){

    //probably unessary
    //this->draw();
    refresh();
    this->pollEvents();

  }

  return 0;
}

int ncursesGui::pollEvents(){

  int event = getch();

  switch (event) {
    case KEY_END:
      this->active = false;
      break;
    case KEY_RESIZE:
      this->redraw();
      break;

    default:
      printw("%d",event);

  }

  return 0;
}

int ncursesGui::draw(){

  this->initSetWin();
  this->initEntryWin();
  this->initProgressWin();
  mvprintw(((COLS)/2),((LINES)/2),"Hello World");

  return 0;
}

int ncursesGui::redraw(){
  clear();
  refresh();
  this->draw();

  return 0;
}

void ncursesGui::initEntryWin(){

  int width = COLS * ENTRYWINWITHRATIO;
  int hight = LINES * ENTRYWINHIGHTRATIO;
  int x = COLS * .5;

  this->entryWin = newwin(hight,width,0,x);
  box(this->entryWin,0,0);

  wrefresh(this->entryWin);

  return;
}

void ncursesGui::initSetWin(){

  int width = COLS * SETWINWITHRATIO;
  int hight = LINES * SETWINHIGHTRATIO;

  this->setWin = newwin(hight,width,0,0);
  box(this->setWin,0,0);

  wrefresh(this->setWin);

  return;
}

void ncursesGui::initProgressWin(){

  int width = COLS * PROGRESSWINWITHRATIO;
  int hight = LINES * PROGRESSWINHIGHTRATIO;

  int y = LINES * .5;

  this->progressWin = newwin(hight,width,y,0);
  box(this->progressWin,0,0);

  wrefresh(this->progressWin);

  return;
}
