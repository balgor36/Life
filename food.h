#ifndef FOOD_H
#define FOOD_H

#define FOOD_COLOR 2

#include "obj.h"

class Food : public Obj {
public:
    Food();
    Food(int x, int y);
    Food(const char* name, int x, int y);
    ~Food();
    bool operator==(const Food& other);

    void draw(WINDOW** win) override;
};

#endif
