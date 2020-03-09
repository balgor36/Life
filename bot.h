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
    void live(std::set<std::shared_ptr<Food>>* foods);
    bool isfoodfounded();
private:
    bool findfood(std::set<std::shared_ptr<Food>>* foods);
    void movetofood(std::set<std::shared_ptr<Food>>* foods);

    int sens;

    // tx, ty - food position
    int tx;
    int ty;

    bool is_food_founded;

    std::weak_ptr<Food> target_food;
};

#endif
