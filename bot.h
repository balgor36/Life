#ifndef BOT_H
#define BOT_H

#define BOT_COLOR 1

#include <vector>
#include <cmath>
#include <cassert>
#include <cfloat>
#include <iostream>
#include "obj.h"
#include "food.h"

class Bot : public Obj {
public:
    Bot();
    Bot(int x, int y);
    Bot(const char* name, int x, int y, int sens);
    ~Bot();

    int getsens();
    void draw(WINDOW** win) override;
    void setsens(int sens);
    void live(std::list<Food>& food);
    bool isfoodfounded();
private:
    bool findfood(std::list<Food>& food);
    void movetofood(std::list<Food>& food);

    int sens;

    // tx, ty - food position
    int tx;
    int ty;

    bool is_food_founded;

    Food* target_food;
};

#endif
