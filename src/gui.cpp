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

    getmaxyx(stdscr,this->Xsize,this->Ysize);
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

  while(this->active){

    this->draw();
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

    default:
      printw("%d",event);

  }

  return 0;
}

int ncursesGui::draw(){

  mvprintw(((this->Xsize)/2),((this->Ysize)/2),"Hello World");

  return 0;
}
