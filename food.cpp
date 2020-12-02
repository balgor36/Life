// Life simulation

// Copyright (c) 2020 Gordey Balaban

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

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
