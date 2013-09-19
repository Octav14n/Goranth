#ifndef TSPIELFELD_H
#define TSPIELFELD_H
#include <list>
#include "src/generic/Macros.h"
#include "tworld.h"
#include "tvec.h"

class TWorld;

class TSpielfeld
{
public:
    enum cheats {
        CHEAT_ADD_FARMER
    };

    DEF_SINGLETON(TSpielfeld)
private:
    std::list<TWorld*> worlds;
    std::shared_ptr<std::vector<std::weak_ptr<TVec>>> selected;
    TWorld *activeWorld;
    int scrollX, scrollY;

    void resetSelection();
    void notifySelected() const;
public:
    void Update();
    void Draw();

    void addWorld(bool setActive = true);
    void setSelectedByArea(int x, int y, int xLength, int yLength);
    void setAction(int x, int y);

    void cheat(cheats cheat, int x, int y);
};

#endif // TSPIELFELD_H
