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

#ifndef OBJ_H
#define OBJ_H

#define PI 3.14159265
#define OBJ_COLOR 0

#include <memory>
#include "pdcurses/curses.h"

struct vec{
    int x = 0;
    int y = 0;
};

class Obj{
public:
    Obj();
    Obj(int x, int y);
    Obj(const char* name, int x, int y);
    ~Obj();

    int getx();
    int gety();
    vec getpos();

    void setx(int x);
    void sety(int y);
    void setcoord(int x, int y);

    void incx();
    void incy();
    void decx();
    void decy();

    void setname(const char* name);
    virtual void draw(WINDOW** win);

    const char* getname();
protected:
    vec pos;
    const char* name;
};

#endif
