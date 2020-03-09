#ifndef OBJ_H
#define OBJ_H

#define PI 3.14159265
#define OBJ_COLOR 0

#include <list>
#include <set>
#include <memory>
#include <ncurses.h>

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
