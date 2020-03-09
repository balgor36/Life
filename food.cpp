#include "food.h"

Food::Food(){
    name = "f";
}

Food::Food(int x, int y){
    this->pos.x = x;
    this->pos.y = y;
    name = "f";
}

Food::Food(const char* name, int x, int y){
    this->pos.x = x;
    this->pos.y = y;
    this->name = name;
}

Food::~Food(){

}

bool Food::operator==(const Food& other){
    if(this->pos.x == other.pos.x && this->pos.y == other.pos.y){
        return true;
    }
    else{
        return false;
    }
}

void Food::draw(WINDOW** win){
    wattron(*win, COLOR_PAIR(FOOD_COLOR));
    mvwprintw(*win, pos.y, pos.x, name);
    wattroff(*win, COLOR_PAIR(FOOD_COLOR));
}
