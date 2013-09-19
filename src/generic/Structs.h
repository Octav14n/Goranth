#ifndef STRUCTS_H
#define STRUCTS_H
#include <SDL2/SDL.h>
#include <memory>
#include "Enums.h"
#include "Interfaces.h"

class TImage;

namespace sVec {
    struct Art {
        eVec::Art art;
        int w, h;
        int maxHealth;
        float rotateGes;
        eBuilding::Art worksOn;
        TImage *image;

        Art(eVec::Art art,
            int w,
            int h,
            int maxHealth,
            float rotateGes,
            eBuilding::Art worksOn,
            TImage *image) :
            art(art),
            w(w), h(h),
            maxHealth(maxHealth),
            rotateGes(rotateGes),
            worksOn(worksOn),
            image(image)
        {}
    };
}

namespace sBuilding {
    struct Art {
        eBuilding::Art art;
        const char *name;
        int w, h;
        int radius;
        int maxHealth;
        int workDelayMS;
        int workMaxVecs;
        eBuilding::Work workArt;
        eVec::Art vecArt;
        TImage *image;

        Art(eBuilding::Art art,
            const char *name,
            int w,
            int h,
            int radius,
            int maxHealth,
            int workDelayMS,
            int workMaxVecs,
            eBuilding::Work workArt,
            eVec::Art vecArt,
            TImage *image) :
            art(art),
            name(name),
            w(w), h(h),
            radius(radius),
            maxHealth(maxHealth),
            workDelayMS(workDelayMS),
            workMaxVecs(workMaxVecs),
            workArt(workArt),
            vecArt(vecArt),
            image(image)
        {}
    };
}

struct sUpdateables {
    Uint32 time;
    std::weak_ptr<iUpdateable> obj;
    bool operator <(const sUpdateables& other) const {
        return (!this->obj.owner_before(other.obj) && !other.obj.owner_before(this->obj)) && (this->time < other.time);
    }
    sUpdateables(Uint32 time, std::weak_ptr<iUpdateable> obj) : time(time), obj(obj) {}
};

#endif // STRUCTS_H
