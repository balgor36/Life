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

#include "bot.h"

Bot::Bot(){
    name = "b";
    sens = rand() % 15;
}

Bot::Bot(int x, int y){
    this->pos.x = x;
    this->pos.y = y;
    name = "b";
    sens = rand() % 15;
}

Bot::Bot(const char* name, int x, int y){
    this->pos.x = x;
    this->pos.y = y;
    this->name = name;
    sens = rand() % 15;
}

Bot::Bot(const char* name, int x, int y, int sens){
    this->pos.x = x;
    this->pos.y = y;
    this->name = name;
    this->sens = sens;
}

Bot::~Bot(){

}

bool Bot::isfoodfounded(){
    return is_food_founded;
}

bool Bot::isdied(){
    return is_died;
}

void Bot::draw(WINDOW** win){
    wattron(*win, COLOR_PAIR(is_died ? DIED_COLOR : BOT_COLOR));
    mvwprintw(*win, pos.y, pos.x, name);
    wattroff(*win, COLOR_PAIR(is_died ? DIED_COLOR : BOT_COLOR));
}

int Bot::getsens(){
    return sens;
}

void Bot::setsens(int sesn){
    this->sens = sens;
}

void Bot::movetofood(std::vector<std::shared_ptr<Obj>>* foods){
    const int deltaX = abs(tx - pos.x);
    const int deltaY = abs(ty - pos.y);
    const int signX = pos.x < tx ? 1 : -1;
    const int signY = pos.y < ty ? 1 : -1;
    //
    int error = deltaX - deltaY;
    //
    if(pos.x != tx || pos.y != ty) 
    {
        const int error2 = error * 2;
        //
        if(error2 > -deltaY) 
        {
            error -= deltaY;
            pos.x += signX;
        }
        if(error2 < deltaX) 
        {
            error += deltaX;
            pos.y += signY;
        }
    }
    if(!target_food.lock()){
        is_food_founded = false;
        tx = ty = -1;
        return;
    }
    if((pos.x == tx && pos.y == ty && target_food.lock())){
        energy++;
        is_food_founded = false;
        tx = ty = -1;
        auto sp = target_food.lock();
        foods->erase(std::remove(foods->begin(), foods->end(), sp), foods->end());
    }
}

void Bot::live(std::vector<std::shared_ptr<Obj>>* foods){    
    if(energy <= 0){
        is_died = true;
        name = "d";
        //foods->insert(std::make_shared<Bot>(Bot(10, 2)));
    }

    if(!is_died){
        static int iter;
        if(!is_food_founded)
            is_food_founded = findfood(foods);

        if(is_food_founded){
            movetofood(foods);
        }
        else{
            if(iter % 3 == 0){
                energy--; 
            }
        }
        iter++;
    }
}

bool Bot::findfood(std::vector<std::shared_ptr<Obj>>* foods){
    bool is_found = false;

    int preva = -1;
    float a;
    int fx, fy;
    for(auto& i : *foods){
        fx = i->getx();
        fy = i->gety();

        a = sqrt(pow(fx-pos.x,2)+pow(fy-pos.y, 2));
        if(a <= sens){
            if(a < preva || preva == -1){
                preva = a;
                tx = fx;
                ty = fy;
                is_found = true;
                target_food = i;
            }
        }
    }
    return is_found;
}

