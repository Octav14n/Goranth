#ifndef TVECMANAGER_H
#define TVECMANAGER_H
#include <memory>
#include <vector>
#include "src/generic/Macros.h"
#include "src/generic/Enums.h"
#include "src/generic/Structs.h"
#include "src/image/tartmanager.h"

class TVecManager
{
    DEF_SINGLETON (TVecManager)
private:
    std::vector<sVec::Art> vecs;
public:
    const sVec::Art *getVec(eVec::Art art) const
    {
        return &this->vecs[static_cast<int>(art)];
    }
};

#endif // TVECMANAGER_H
