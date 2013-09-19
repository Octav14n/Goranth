#ifndef TFARMER_H
#define TFARMER_H
#include "timage.h"
#include "tvec.h"

class TVec;

class TFarmer : public TVec
{
private:
    static TImage *image;
protected:
    bool doWORK();
public:
    TFarmer(int x, int y) : TVec(1, TFarmer::image, x, y){}

    static void Init() {
        if (image == NULL) {
            TFarmer::image = new TImage("./image/Icon.png");
        }
    }
};

#endif // TFARMER_H
