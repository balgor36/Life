#include <chrono>
#include <cstdlib>
#include <fstream>
#include "bot.h"
#include "food.h"

#define randf()\
    static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

typedef std::chrono::high_resolution_clock Clock;

std::vector<Bot> bots;
std::list<Food> foods;
WINDOW* win;
int height, width, start_y, start_x;

// food spawn rate 
const float FOOD_RATE = 10.0f;
const float BOTS_RATE = 1.0f;

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

    if(!has_colors()){
        endwin();
        printf("Terminal does not support colors");
        return -1;
    }
    start_color();
    use_default_colors();

    init_pair(OBJ_COLOR, COLOR_BLACK, COLOR_BLUE);
    init_pair(BOT_COLOR, COLOR_BLACK, COLOR_GREEN); 
    init_pair(FOOD_COLOR, COLOR_BLACK, COLOR_CYAN);
    refresh();

    int food_size = (width-1)*(height-1)*(FOOD_RATE/100.0f);

    for(int ii = 0; ii < food_size; ++ii){
        int x, y;
        x = rand() % (width-2) + 1;
        y = rand() % (height-2) + 1;
        foods.push_back(Food(x, y));
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

    while(x_x < 200){
//        int c = wgetch(win);
        t2 = Clock::now();
        if(std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count() > 100){
            x_x++;
            t1 = t2;
            werase(win);
            for(auto& food : foods)
                food.draw(&win);
            for(auto& bot : bots){
                bot.draw(&win);
                bot.live(foods);
            }
            box(win, 0, 0);
           
            stats();

            wrefresh(win);
        }
    }
    endwin(); 
    return 0;
}
