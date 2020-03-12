#ifndef BOT_H
#define BOT_H

#define BOT_COLOR 1
#define DIED_COLOR 3 

// iteration to die without food
#define ENERGY_TO_REPRODUCE 10

#include <vector>
#include <cmath>
#include <cassert>
#include <cfloat>
#include <iostream>
#include <string>
#include "obj.h"
#include "food.h"

class Bot : public Obj {
public:
    Bot();
    Bot(int x, int y);
    Bot(const char* name, int x, int y);
    Bot(const char* name, int x, int y, int sens);
    ~Bot();

    int getsens();
    void draw(WINDOW** win) override;
    void setsens(int sens);
    void live(std::set<std::shared_ptr<Obj>>* foods);
    bool isfoodfounded();
    bool isdied();
private:
    bool findfood(std::set<std::shared_ptr<Obj>>* foods);
    void movetofood(std::set<std::shared_ptr<Obj>>* foods);
    bool is_died = false;

    int energy = 5;

    int sens;

    // tx, ty - food position
    int tx;
    int ty;

    bool is_food_founded;

    std::weak_ptr<Obj> target_food;
};

#endif
