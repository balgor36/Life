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

void Bot::draw(WINDOW** win){
    wattron(*win, COLOR_PAIR(BOT_COLOR));
    mvwprintw(*win, pos.y, pos.x, name);
    wattroff(*win, COLOR_PAIR(BOT_COLOR));
}

int Bot::getsens(){
    return sens;
}

void Bot::setsens(int sesn){
    this->sens = sens;
}

void Bot::movetofood(std::set<std::shared_ptr<Food>>* foods){

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
        is_food_founded = false;
        tx = ty = -1;
        auto sp = target_food.lock();
        foods->erase(sp);
    }
}

void Bot::live(std::set<std::shared_ptr<Food>>* foods){
    if(!is_food_founded)
        is_food_founded = findfood(foods);

    if(is_food_founded){
        movetofood(foods);
    }
}

bool Bot::findfood(std::set<std::shared_ptr<Food>>* foods){
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

