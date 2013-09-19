#ifndef TWORLD_H
#define TWORLD_H
#include <memory>
#include <set>
#include "src/generic/Interfaces.h"
#include "tbuilding.h"
#include "tvec.h"

class TSpielfeld;
class TBuilding;
class TVec;

class TWorld : public iUpdateable, public iDrawable
{
private:
    std::set <std::shared_ptr<TBuilding> > gebaeude;
    std::set <std::weak_ptr<TVec>, std::owner_less<std::weak_ptr<TVec> > > vehicle;
    std::multiset <sUpdateables> updateables;
    const TSpielfeld *spielfeld;

    bool addUpdateable(std::weak_ptr<iUpdateable> updateable, Uint32 time);
public:
    TWorld(TSpielfeld *spielfeld);
    ~TWorld();

    void draw(int scrollX, int scrollY) const;
    Uint32 update();
    void update(std::shared_ptr<iUpdateable> obj);

    std::shared_ptr<std::vector <std::weak_ptr<TVec>>> getVecFromRect(int xStart, int yStart, int xEnd, int yEnd) const;
    std::weak_ptr <TBuilding> getBuildingFromPoint(int x, int y) const;
    std::shared_ptr<std::vector <std::weak_ptr<TBuilding> > > getBuildingFromPoint(int x, int y, int range, std::shared_ptr<TVec> vec = NULL) const;

    inline void addBuilding(std::shared_ptr<TBuilding> building) {
        gebaeude.insert(building);
    }

    void removeBuilding(std::shared_ptr<TBuilding> building);

    inline void addVec(std::weak_ptr<TVec> vec) {
        vehicle.insert(vec);
    }
};

#endif // TWORLD_H
