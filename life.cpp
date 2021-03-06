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

#include <chrono>
#include <cstdlib>
#include <fstream>
#include "bot.h"
#include "food.h"

#define randf()\
    static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

typedef std::chrono::high_resolution_clock Clock;

std::vector<Bot> bots;
std::vector<std::shared_ptr<Obj>> foods;
WINDOW* win;
int height, width, start_y, start_x;

// food spawn rate 
float FOOD_RATE = 10.0f;
float BOTS_RATE = 3.0f;

void stats(){
    mvwprintw(win, height-1, 1, "foods: %d | bots: %d", foods.size(), bots.size());
}

int main(){
    srand(std::time(0));

    initscr();
    noecho();

    start_y = start_x = 0;
    getmaxyx(stdscr, height, width);
    
    win = newwin(height, width, start_y, start_x);
	
	std::ifstream infile("config.txt");
	if(!infile.is_open()){
		infile.close();
	}
	else{
		infile >> FOOD_RATE >> BOTS_RATE;
	}

    if(!has_colors()){
        endwin();
        printf("Terminal does not support colors");
        return -1;
    }
    start_color();
    use_default_colors();

    init_pair(OBJ_COLOR, COLOR_BLACK, COLOR_BLUE);
    init_pair(BOT_COLOR, COLOR_BLACK, COLOR_GREEN); 
    init_pair(FOOD_COLOR, COLOR_BLACK, COLOR_MAGENTA);

    init_pair(DIED_COLOR, COLOR_YELLOW, COLOR_BLACK);

    refresh();

    int food_size = (width-1)*(height-1)*(FOOD_RATE/100.0f);

    for(int ii = 0; ii < food_size; ++ii){
        int x, y;
        x = rand() % (width-2) + 1;
        y = rand() % (height-2) + 1;
        foods.push_back(std::make_shared<Food>(x, y));
    }

    bots.resize((width-1)*(height-1)*(BOTS_RATE/100.0f));
    for(auto& i : bots){
        int x, y;
        x = rand() % (width-2) + 1;
        y = rand() % (height-2) + 1;
        i = Bot("b", x, y, (rand() % 30)+1);
    }
//    foods.push_back(Food(rand() % (width-2)+1, rand() % (height-2)+1));
//    bots.push_back(Bot("b", (rand() % (width-2))+1, (rand() % (height-2))+1, 15000));

    std::chrono::time_point<Clock> t1 = Clock::now();
    std::chrono::time_point<Clock> t2;

    int x_x = 0;

    while(bots.size() > 0){
        t2 = Clock::now();
        if(std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count() > 50){
            x_x++;
            t1 = t2;
            werase(win);
            for(auto& food : foods)
                food->draw(&win);
            for(std::vector<Bot>::iterator it = bots.begin(); it != bots.end(); ++it){
                if(it->isdied()){
                    bots.erase(it);
                    it--;   
                    continue;
                }
                it->draw(&win);
                it->live(&foods);
            }
            box(win, 0, 0);
           
            stats();

            wrefresh(win);
        }
    }
    endwin(); 
    return 0;
}
