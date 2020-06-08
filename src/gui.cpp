#include "gui.hpp"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

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
    noecho();

    if(has_colors() == FALSE){
      endwin();
		  std::cout << "Your terminal does not support color" << std::endl;
      exit();
    }

    start_color();
    init_pair(ERRORCOLOR, COLOR_RED, COLOR_BLACK);
    init_pair(FINECOLOR, COLOR_GREEN, COLOR_BLACK);
    init_pair(WORKINGCOLOR, COLOR_CYAN, COLOR_BLACK);

    this->allocated = true;

    return 0;
}

int ncursesGui::exit(){

  if(this->allocated){
    this->clearForms();
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

    case 9:
      if (this->activeForm == this->entryForm){
        this->activeForm = this->setForm;
      } else {
        this->activeForm = this->entryForm;
      }
      break;

    case KEY_F(1):
      this->startGenerating();
      break;

    case KEY_F(2):
      break;

    case KEY_F(3):
      this->setFile = !(this->setFile);
      this->printLables(this->labelColors);
      break;

    default:
      this->formInputHandler(event);
      break;

  }

  return 0;
}

int ncursesGui::draw(){

  this->initSetWin();
  this->initEntryWin();
  this->initProgressWin();
  this->printLables(this->labelColors);

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

  this->initEntryForm(width,hight);

  box(this->entryWin,0,0);

  wrefresh(this->entryWin);

  return;
}

void ncursesGui::initSetWin(){

  int width = COLS * SETWINWITHRATIO;
  int hight = LINES * SETWINHIGHTRATIO;

  this->setWin = newwin(hight,width,0,0);

  this->initSetForm(width,hight);

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

  wattron(this->progressBar,COLOR_PAIR(FINECOLOR));
  mvwprintw(this->progressBar,1,1,fill.c_str());
  wattroff(this->progressBar,COLOR_PAIR(FINECOLOR));

  mvwprintw(this->progressBar,1,1 + fillLength/2 - 2,"%.1f%%", percentage * 100);

  wrefresh(this->progressBar);

  return;
}

void ncursesGui::initSetForm(int width, int hight){

  //TODO: clean up this form init with memory clearing

  this->setField[0] = new_field(hight - 4 , width - 4, 2, 2,0,0);
  this->setField[1] = NULL;

  set_field_back(this->setField[0], A_UNDERLINE);
  field_opts_off(this->setField[0], O_AUTOSKIP);

  this->setForm = new_form(this->setField);

  set_form_win(this->setForm, this->setWin);
  set_form_sub(this->setForm, derwin(this->setWin, hight, width, 2, 2));
  post_form(this->setForm);

  return;
}

void ncursesGui::initEntryForm(int width, int hight){

  //TODO: clean up this form init with memory clearing

  for(int i = 0; i < 5; i++){
    this->entryField[i] = new_field( 1 , width - 4, 2 + (i * 2) , 2,0,0);
    set_field_back(this->entryField[i], A_UNDERLINE);
    field_opts_off(this->entryField[i], O_AUTOSKIP);
    if (i < 3){
      set_field_type(this->entryField[i], TYPE_INTEGER, 0, 0, 0);
    }

  }

  this->entryField[5] = NULL;

  this->entryForm = new_form(this->entryField);
  this->activeForm = this->entryForm;

  set_form_win(this->entryForm, this->entryWin);
  set_form_sub(this->entryForm, derwin(this->entryWin, hight, width, 2, 2));
  post_form(this->entryForm);

  return;
}

void ncursesGui::printLables(int colors[7]){


  wattron(this->setWin,COLOR_PAIR(colors[0]));
  mvwprintw(this->setWin,1,1,"Set:");
  wattroff(this->setWin,COLOR_PAIR(colors[0]));

  wrefresh(this->setWin);

  std::string lables[] = ENTRYLABLES;

  int i = 0;
  for(; i < 5; i++){
    wattron(this->entryWin,COLOR_PAIR(colors[i + 1]));
    mvwprintw(this->entryWin, 1 + (i * 2), 1, lables[i].c_str() );
    wattroff(this->entryWin,COLOR_PAIR(colors[i + 1]));
  }

  wattron(this->entryWin,COLOR_PAIR(colors[i + 1]));
  mvwprintw(this->entryWin, 1 + (i * 2), 1,STARTLABLE );
  wattroff(this->entryWin,COLOR_PAIR(colors[i + 1]));

  wattron(this->entryWin,COLOR_PAIR(colors[i + 2]));
  mvwprintw(this->entryWin, 1 + (i * 2), 1 + sizeof(STARTLABLE), STOPLABLE );
  wattroff(this->entryWin,COLOR_PAIR(colors[i + 2]));

  std::string toPrint;
  if (this->setFile){
    toPrint = SETFILE;
  } else {
    toPrint = SETTEXT;
  }

  wattron(this->entryWin,COLOR_PAIR(colors[i + 3]));
  mvwprintw(this->entryWin, 1 + (i * 2), 1 + sizeof(STARTLABLE) + sizeof(STOPLABLE), toPrint.c_str() );
  wattroff(this->entryWin,COLOR_PAIR(colors[i + 3]));



  wrefresh(this->entryWin);

}

void ncursesGui::formInputHandler(int input){

  form_driver(this->activeForm, REQ_END_FIELD);

  switch (input) {
    case KEY_UP:
      form_driver(this->activeForm, REQ_VALIDATION);
      form_driver(this->activeForm, REQ_PREV_FIELD);
      form_driver(this->activeForm, REQ_END_LINE);
      break;

    case KEY_DOWN:
      form_driver(this->activeForm, REQ_VALIDATION);
      form_driver(this->activeForm, REQ_NEXT_FIELD);
      form_driver(this->activeForm, REQ_END_LINE);
      break;

    case 127:
    case KEY_BACKSPACE:
      form_driver(this->activeForm,REQ_DEL_CHAR);
      break;
    default:
      form_driver(this->activeForm,input);
      break;
  }

  wrefresh(this->entryWin);
  wrefresh(this->setWin);

  return;
}

void ncursesGui::clearForms(){

  this->activeForm = NULL;

  unpost_form(this->entryForm);
  unpost_form(this->setForm);

  free_form(this->entryForm);
  free_form(this->setForm);

  for(int i = 0; i < 5; i++){
    free_field(this->entryField[i]);
    this->entryField[i] = NULL;
  }

  free_field(this->setField[0]);
  this->setField[0] = NULL;

  return;
}

void ncursesGui::startGenerating(){

  this->labelColors[6] = WORKINGCOLOR;
  this->printLables(labelColors);

  int stringNumber;
  int stringLength;
  int threadNumber;
  std::string saveFile;
  std::string charSet;

  std::sscanf(field_buffer(this->entryField[0],0),"%d",&stringNumber);
  std::sscanf(field_buffer(this->entryField[1],0),"%d",&stringLength);
  std::sscanf(field_buffer(this->entryField[2],0),"%d",&threadNumber);
  saveFile = field_buffer(this->entryField[3],0);

  if(this->setFile){

    std::ifstream setfile(field_buffer(this->entryField[4],0));

    if(!(setfile.is_open())){
      this->labelColors[6] = FINECOLOR;
      this->printLables(labelColors);
      return;
    }

    std::stringstream buffer;
    buffer << setfile.rdbuf();

    charSet = buffer.str();
  } else {
    charSet = field_buffer(this->setField[0],0);
  }

//changed this as soon as possable couldnt becuse lacked necceary function in stringGen
  this->generator = new stringGen(stringLength);
  this->generator->setCharSet(charSet);

  if (this->generator->posableGen(stringNumber) != 0){
    this->labelColors[6] = FINECOLOR;
    this->printLables(labelColors);
    return;
  }

  this->generator->stringThreadHandler(threadNumber,stringNumber);
  this->genrating = stringNumber;

  return;
}
