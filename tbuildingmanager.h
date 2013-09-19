#ifndef TBUILDINGMANAGER_H
#define TBUILDINGMANAGER_H
#include <list>
#include <vector>
#include "src/generic/Macros.h"
#include "src/generic/Enums.h"
#include "src/generic/Structs.h"
#include "src/image/tartmanager.h"

class TBuilding;
class TVec;



class TBuildingManager
{
    DEF_SINGLETON (TBuildingManager)
private:
    std::vector<sBuilding::Art> buildings;
public:
    const sBuilding::Art * getBuilding(eBuilding::Art art) const
    {
        return &this->buildings[static_cast<int>(art)];
    }
};

#endif // TBUILDINGMANAGER_H
