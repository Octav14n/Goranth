#include "tbuildingmanager.h"

TBuildingManager::TBuildingManager() : buildings()
{
	this->buildings.push_back(sBuilding::Art(eBuilding::Art::Weizenfeld,
                           "Weizenfeld",
                           20, 20,
                           0,
                           100,
                           12 * 5,
                           1,
                           eBuilding::Work::Feld,
                           eVec::Art::Farmer,
                           TArtManager::instance().getImage(eImage::BFeld)));
    this->buildings.push_back(sBuilding::Art(eBuilding::Art::Weizenfarm,
                           "Weizenfarm",
                           20, 20,
                           2000,//50,
                           100,
                           2500,
                           2,
                           eBuilding::Work::Farm,
                           eVec::Art::Farmer,
                           TArtManager::instance().getImage(eImage::BFarm)));
}
