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

#ifndef BOT_H
#define BOT_H

#define BOT_COLOR 1
#define DIED_COLOR 3 

// iteration to die without food
#define ENERGY_TO_REPRODUCE 10

#include <vector>
#include <cmath>
#include <cfloat>
#include <iostream>
#include <string>
#include <algorithm> //std::remove
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
    void live(std::vector<std::shared_ptr<Obj>>* foods);
    bool isfoodfounded();
    bool isdied();
private:
    bool findfood(std::vector<std::shared_ptr<Obj>>* foods);
    void movetofood(std::vector<std::shared_ptr<Obj>>* foods);
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
