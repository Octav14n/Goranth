#ifndef INTERFACES_H
#define INTERFACES_H
#include <SDL2/SDL.h>

class iUpdateable
{
public:
    virtual Uint32 update() = 0;
};

class iDrawable
{
public:
    virtual void draw(int scrollX, int scrollY) const = 0;
};

#endif // INTERFACES_H
