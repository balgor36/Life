#include "obj.h"

Obj::Obj(){
    name = "o";
}

Obj::Obj(int x, int y){
    this->pos.x = x;
    this->pos.y = y;
    name = "o";
}

Obj::Obj(const char* name, int x, int y){
    this->pos.x = x;
    this->pos.y = y;
    this->name = name;
}

Obj::~Obj(){

}

vec Obj::getpos(){
    return pos;
}

void Obj::incx(){
    pos.x++;
}

void Obj::incy(){
    pos.y++;
}

void Obj::decx(){
    pos.x--;
}

void Obj::decy(){
    pos.y--;
}

int Obj::getx(){
    return pos.x;
}

int Obj::gety(){
    return pos.y;
}

void Obj::setx(int x){
    this->pos.x = x;
}

void Obj::sety(int y){
    this->pos.y = y;
}

void Obj::setcoord(int x, int y){
    this->pos.x = x;
    this->pos.y = y;
}

void Obj::setname(const char* name){
    this->name = name;
}

const char* Obj::getname(){
    return this->name;
}

void Obj::draw(WINDOW** win){
    wattron(*win, COLOR_PAIR(OBJ_COLOR));
    mvwprintw(*win, pos.y, pos.x, name);
    wattroff(*win, COLOR_PAIR(OBJ_COLOR));
}
