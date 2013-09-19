#ifndef TBUILDINGFELD_H
#define TBUILDINGFELD_H
#include "tbuilding.h"
#include "tspielfeld.h"

class TBuildingFeld : public TBuilding
{
private:
    static const TImage *image;
public:
    TBuildingFeld(int x, int y) : TBuilding(x, y, 100, TBuildingFeld::image) {Init();}
    static void Init() {
        if (image == NULL) {
            TBuildingFeld::image = new TImage("./image/feld.png");
        }
    }
};

#endif // TBUILDINGFELD_H
