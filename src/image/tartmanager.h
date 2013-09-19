#ifndef TARTMANAGER_H
#define TARTMANAGER_H
#include <SDL2/SDL.h>
#include "timage.h"
#include "src/generic/Macros.h"
#include "src/generic/Enums.h"

class TArtManager
{
public:
    DEF_SINGLETON (TArtManager)
private:
    TImage *image[eImage::COUNT];
public:

    TImage *getImage(eImage::Enum img) {
        return this->image[img];
    }

};

#endif // TARTMANAGER_H
