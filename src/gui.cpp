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

    if(has_colors() == FALSE){
      endwin();
		  printf("Your terminal does not support color\n");
      exit();
    }

    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);

    this->allocated = true;

    return 0;
}

int ncursesGui::exit(){

  if(this->allocated){
    this->clearWindows();
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

  return 0;
}

int ncursesGui::redraw(){

  this->clearWindows();

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

  this->progressBarWidth = width - PROGRESSBAROFFSET * 2 - 2;
  this->percentPosition = width - PROGRESSBAROFFSET * 2 + PROGRESSBAROFFSET + 1;

  this->progressWin = newwin(hight,width,y,0);
  this->progressBar = newwin(3,this->progressBarWidth + 2,y + PROGRESSBAROFFSET, PROGRESSBAROFFSET);
  box(this->progressWin,0,0);
  box(this->progressBar,0,0);

  wrefresh(this->progressWin);
  wrefresh(this->progressBar);

  return;
}

void ncursesGui::clearWindows(){

  delwin(this->entryWin);
  delwin(this->setWin);
  delwin(this->progressWin);
  delwin(this->progressBar);

  return;
}

void ncursesGui::setProgressBar(float percentage){

  int fillLength = percentage * this->progressBarWidth;
  std::string fill(fillLength - 1,PROGRESSBARCHAR);
  fill += PROGRESSBARENDCHAR;

  wattron(this->progressBar,COLOR_PAIR(2));
  mvwprintw(this->progressBar,1,1,fill.c_str());
  wattroff(this->progressBar,COLOR_PAIR(2));

  mvwprintw(this->progressBar,1,1 + fillLength/2 - 2,"%.1f%%", percentage * 100);

  wrefresh(this->progressBar);

  return;
}
