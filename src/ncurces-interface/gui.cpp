#include "gui.hpp"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

#define TRIMEND(x) x.erase(x.find_last_not_of(" ")+1)

ncursesGui::ncursesGui(){

  return;
}

ncursesGui::~ncursesGui(){

  this->exit();
}

int ncursesGui::init(){

  initscr();
  keypad(stdscr, TRUE);
  timeout(10);
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
  this->generator.terminateThreads();
  this->generator.clearMemory(true,true,true);
  return 0;
}

int ncursesGui::mainLoop(){

  this->active = true;

  refresh();
  this->draw();



  while(this->active){

    //probably unnecessary
    //this->draw();
    this->updateStatus();
    refresh();
    pos_form_cursor(this->activeForm);
    this->pollEvents();

  }

  return 0;
}

int ncursesGui::pollEvents(){


  int event = wgetch(form_win(this->activeForm));

  switch (event) {
    case KEY_END:
      this->active = false;
      break;
    case KEY_RESIZE:
      this->redraw();
      break;

    case KEY_F(1):
      this->startGenerating();
      break;

    case KEY_F(2):
      this->stopGenerating();
      break;

    case KEY_F(3):
      this->setFile = !(this->setFile);
      this->printLabels(this->labelColors);
      break;

    case ERR:
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
  this->printLabels(this->labelColors);
  keypad(this->setWin, TRUE);
  keypad(this->entryWin, TRUE);
  wtimeout(this->setWin,10);
  wtimeout(this->entryWin,10);

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
  this->progressBar = newwin(PROGRESSBARHEIGHT,this->progressBarWidth + 2,y + PROGRESSBAROFFSET, PROGRESSBAROFFSET);
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

  if(percentage <= 0){
    wclear(this->progressBar);
    box(this->progressBar,0,0);
    wrefresh(this->progressBar);
    return;
  }

  int fillLength = percentage * (this->progressBarWidth - 2);
  std::string fill(fillLength,PROGRESSBARCHAR);
  fill += PROGRESSBARENDCHAR;

  wattron(this->progressBar,COLOR_PAIR(FINECOLOR));
  mvwprintw(this->progressBar,1,1,fill.c_str());
  wattroff(this->progressBar,COLOR_PAIR(FINECOLOR));

  mvwprintw(this->progressBar,1,this->progressBarWidth/2,"%2.1f%%", percentage * 100);

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

void ncursesGui::printLabels(int colors[7]){


  wattron(this->setWin,COLOR_PAIR(colors[0]));
  mvwprintw(this->setWin,1,1,"Set:");
  wattroff(this->setWin,COLOR_PAIR(colors[0]));

  wrefresh(this->setWin);

  std::string labels[] = ENTRYLABELS; //edit @6.27.20

  int i = 0;
  for(; i < 5; i++){
    wattron(this->entryWin,COLOR_PAIR(colors[i + 1]));
    mvwprintw(this->entryWin, 1 + (i * 2), 1, labels[i].c_str() );
    wattroff(this->entryWin,COLOR_PAIR(colors[i + 1]));
  }

  wattron(this->entryWin,COLOR_PAIR(colors[i + 1]));
  mvwprintw(this->entryWin, 1 + (i * 2), 1,STARTLABEL );
  wattroff(this->entryWin,COLOR_PAIR(colors[i + 1]));

  wattron(this->entryWin,COLOR_PAIR(colors[i + 2]));
  mvwprintw(this->entryWin, 1 + (i * 2), 1 + sizeof(STARTLABEL), STOPLABEL );
  wattroff(this->entryWin,COLOR_PAIR(colors[i + 2]));

  std::string toPrint;
  if (this->setFile){
    toPrint = SETFILE;
  } else {
    toPrint = SETTEXT;
  }

  wattron(this->entryWin,COLOR_PAIR(colors[i + 3]));
  mvwprintw(this->entryWin, 1 + (i * 2), 1 + sizeof(STARTLABEL) + sizeof(STOPLABEL), toPrint.c_str() );
  wattroff(this->entryWin,COLOR_PAIR(colors[i + 3]));



  wrefresh(this->entryWin);

}

void ncursesGui::formInputHandler(int input){

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
      form_driver(this->activeForm,REQ_DEL_PREV );
      break;

    case KEY_RIGHT:
      form_driver(this->activeForm,REQ_NEXT_CHAR);
      break;

    case KEY_LEFT:
      form_driver(this->activeForm,REQ_PREV_CHAR);
      break;

    case 9:
      if (form_driver(this->activeForm, REQ_VALIDATION) == E_INVALID_FIELD) break;

      form_driver(this->activeForm, REQ_NEXT_FIELD);
      form_driver(this->activeForm, REQ_PREV_FIELD);

      if (this->activeForm == this->entryForm){
        this->activeForm = this->setForm;
      } else {
        this->activeForm = this->entryForm;
      }
      break;

    default:
      form_driver(this->activeForm,input);
      break;
  }

  wrefresh(form_win(this->activeForm));

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

  form_driver(this->activeForm, REQ_NEXT_FIELD);
  form_driver(this->activeForm, REQ_PREV_FIELD);

  this->labelColors[6] = WORKINGCOLOR;
  this->printLabels(labelColors);

  int stringNumber;
  int stringLength;
  int threadNumber;

  std::string charSet;

  std::sscanf(field_buffer(this->entryField[0],0),"%d",&stringNumber);
  std::sscanf(field_buffer(this->entryField[1],0),"%d",&stringLength);
  std::sscanf(field_buffer(this->entryField[2],0),"%d",&threadNumber);


  if(this->setFile){
    std::string setName = field_buffer(this->entryField[4],0);
    std::ifstream setfile(TRIMEND(setName));

    if(!(setfile.is_open())){
      this->labelColors[6] = FINECOLOR;
      this->printLabels(labelColors);
      return;
    }

    std::getline(setfile,charSet);

  } else {
    charSet = field_buffer(this->setField[0],0);
  }

  charSet = TRIMEND(charSet);

  if (this->generating != 0){
    return;
  }

  this->generator.clearMemory(true,true,true);
  this->generator.setStringLength(stringLength);
  this->generator.setCharSet(charSet);


  if (this->generator.possibleGen(stringNumber) != 0){
    this->labelColors[6] = FINECOLOR;
    this->printLabels(labelColors);
    return;
  }

  this->generator.stringThreadHandler(threadNumber,stringNumber);
  this->generating = stringNumber;

  return;
}

void ncursesGui::stopGenerating() {
  this->labelColors[6] = ERRORCOLOR;
  this->printLabels(labelColors);

  this->generator.terminateThreads();
  this->generator.clearMemory(true,false,false);

  this->labelColors[6] = FINECOLOR;
  this->printLabels(labelColors);

  this->generating = 0;
  this->setProgressBar(0.0);

  return;
}

void ncursesGui::generatingComplete(){

  form_driver(this->activeForm, REQ_NEXT_FIELD);
  form_driver(this->activeForm, REQ_PREV_FIELD);

  std::string saveFile;
  saveFile = field_buffer(this->entryField[3],0);

  std::ofstream savefile(TRIMEND(saveFile));

  if(!(savefile.is_open())){
    this->labelColors[6] = ERRORCOLOR;
    this->printLabels(labelColors);
    return;
  }

  std::list<std::string> toWrite = this->generator.returnList();
  std::list<std::string> :: iterator itr;
  for ( itr = toWrite.begin(); itr != toWrite.end(); itr++){
    savefile << (*itr) << '\n';
  }

  savefile.close();

  this->generator.clearMemory(false,true,false);

  this->stopGenerating();

  return;
}

void ncursesGui::updateStatus(){
  if(this->generating == 0){
    return;
  }
  int generated = this->generator.returnListLen();

  float percentage = float(generated)/float(this->generating);

  std::stringstream statusbuff;
  std::string status;
  statusbuff << "Generating " << generated << "/" << generating;
  status = statusbuff.str();
  status.resize(this->progressBarWidth + 2);

  this->setProgressBar(percentage);

  mvwprintw(this->progressWin, PROGRESSBAROFFSET + PROGRESSBARHEIGHT, PROGRESSBAROFFSET, status.c_str());
  wrefresh(this->progressWin);

  if(percentage >= 1){
    this->generatingComplete();
  }
  return;
}
