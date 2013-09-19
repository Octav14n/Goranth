#ifndef TVEC_H
#define TVEC_H
#include <math.h>
#include "src/generic/Interfaces.h"
#include "tvecmanager.h"
#include "tworld.h"
#define INC_SHARED( NAME ) public std::enable_shared_from_this<NAME>

class TBuilding;
class TWorld;

class TVec : public iUpdateable, public iDrawable, INC_SHARED(TVec)
{
private:
    inline float sin(float angle) const {
        return static_cast<float>(::sin(angle * M_PI / 180));
    }
    inline float cos(float angle) const{
        return static_cast<float>(::cos(angle * M_PI / 180));
    }
    float x, y, xZiel, yZiel, angle, angleZiel;
    eVec::Action aktion;
    Uint32 nextWork;
    bool selected;
    const sVec::Art *art;
    TWorld *world;
    const TImage *image;

    std::weak_ptr<TBuilding> homeBuilding;
    std::weak_ptr<TBuilding> workBuilding;

    bool doIDLE();
    bool doROTATE();
    bool doMOVE();
    Uint32 doWORK();

    void returnHome();
public:
    void draw(int scrollX, int scrollY) const;
    Uint32 update();
    TVec(int x, int y, const sVec::Art *type, std::weak_ptr<TBuilding> homeBuilding, TWorld *world);
    ~TVec() {
        printf("Destroying TVec: %i\n", static_cast<int>(art->art));
    }

    void setZiel(int x, int y);
    void setZiel(std::shared_ptr<TBuilding> build);

    inline void setSelected(bool state)
    {
        printf("Selected Vec(%p): %i\n", this, state);
        this->selected = state;
    }

    eVec::Action getAktion() const {
        return this->aktion;
    }
    
    eVec::Art getArt() const {
        return this->art->art;
    }

    void setWorking(std::weak_ptr<TBuilding> building);

    inline bool isInRect(int xStart, int yStart, int xLength, int yLength) const{
        return (this->x > xStart && this->x < xStart + xLength) && (this->y > yStart && this->y < yStart + yLength);
    }

    bool isHome() const;
};

#endif // TVEC_H
