#ifndef TBUILDING_H
#define TBUILDING_H
#include <vector>
#include <memory>
#include "src/generic/Interfaces.h"
#include "tbuildingmanager.h"
#include "tvec.h"
#define INC_SHARED( NAME ) public std::enable_shared_from_this<NAME>

class TVec;
class TWorld;

class TBuilding : public iUpdateable, public iDrawable, INC_SHARED(TBuilding)
{
private:
    int x, y;
    int health;
    Uint32 nextWork;
    std::vector<std::shared_ptr<TVec> > workVecs;
    const sBuilding::Art * const art;
    TWorld *world;
public:
    Uint32 update();
    void draw(int scrollX, int scrollY) const;
    bool isPointIn(int x, int y) const;

    TBuilding(int x, int y, const sBuilding::Art *type, TWorld *world);

    Uint32 doWORK(std::shared_ptr<TVec> vec = std::shared_ptr<TVec>());

    bool isWorkable() {
        return this->isWorkable(std::shared_ptr<TVec>());
    }
    bool isWorkable(std::shared_ptr<TVec> vec);

    inline bool isInRect(int xStart, int yStart, int xLength, int yLength) const{
        return (this->x + this->width() > xStart && this->x < xStart + xLength) && (this->y + this->height() > yStart && this->y < yStart + yLength);
    }

    inline int getX() const
    {
        return this->x;
    }

    inline int getY() const
    {
        return this->y;
    }

    inline int width() const
    {
        return this->art->w;
    }

    inline int height() const
    {
        return this->art->h;
    }
};

#endif // TBUILDING_H
