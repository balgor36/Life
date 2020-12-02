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
