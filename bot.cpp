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

void Bot::movetofood(std::list<Food>& food){
    if(tx-pos.x != 0){
        x_flt += 0.1f*((static_cast<float>(ty-pos.y))/(static_cast<float>(tx-pos.x)));
//        y_flt = (((x_flt-sx)*(tx-sy))/(tx-sx)) + sy;
        y_flt = ((x_flt-sx)*(ty-sy))/static_cast<float>(tx-sx) + sy;
        
    }
    else{
        if(pos.y > ty)
            y_flt--;
        else
            y_flt++; 
    }
    
    pos.x = static_cast<int>(x_flt);
    pos.y = static_cast<int>(y_flt);

    if(pos.y > ty){
        if(pos.x > tx){
            // первая четверть
            p_dir = 1;
        }
        else if(pos.x < tx){
            // вторая четверть
            p_dir = 2;
        }
        else if(pos.x == tx){
            p_dir = 5;
        }
    } 
    else if(pos.y < ty){
        if(pos.x > tx){
            // четвертая четверть
            p_dir = 4;
        }
        else if(pos.x < tx){
            // третья четверть
            p_dir = 3;
        }
        else if(pos.x == tx){
            p_dir = 7;
        }
    }
    else if(pos.y == ty){
        if(pos.x > tx){
            p_dir = 8;
        }
        else if(pos.x < tx){
            p_dir = 6;
        }
        else if(pos.x == tx){
            p_dir = 0;
        }
    }

    //if(pos.x == tx && pos.y == ty){
    if(p_dir == 0 || last_dir != p_dir){
        is_food_founded = false;
        tx = ty = sx = sy = x_flt = y_flt = -1;
        food.remove(*target_food);
        //        food.erase(food.begin() + (target_food - &food[0]));
        target_food = nullptr;
    }
    last_dir = p_dir;
}

void Bot::live(std::list<Food>& food){
    if(!is_food_founded)
        is_food_founded = findfood(food);

    if(is_food_founded){
        x_flt = static_cast<float>(pos.x);
        y_flt = static_cast<float>(pos.y);
        movetofood(food);
    }
}

bool Bot::findfood(std::list<Food>& food){
    bool is_found = false;
    int preva = -1;
    float a;
    int fx, fy;
    for(auto& i : food){
        fx = i.getx();
        fy = i.gety();

        a = sqrt(pow(fx-pos.x,2)+pow(fy-pos.y, 2));
        if(a <= sens){
            if(a < preva || preva == -1){
                preva = a;
                tx = fx;
                ty = fy;
                sx = pos.x;
                sy = pos.y;
                is_found = true;
                target_food = &i;
            }
        }
    }
    return is_found;
}

