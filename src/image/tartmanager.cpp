#include "tartmanager.h"

TArtManager::TArtManager() {
    this->image[eImage::BFeld] = new TImage("./image/feld.png");
    this->image[eImage::BFarm] = new TImage("./image/farm.png");
    this->image[eImage::VFarmer] = new TImage("./image/Icon.png");
}
