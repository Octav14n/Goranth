#include "tvecmanager.h"


TVecManager::TVecManager() : vecs()
{
	this->vecs.push_back(sVec::Art(
                    eVec::Art::Farmer,
                    16, 16,
                    100,
                    1.0,
                    eBuilding::Art::Weizenfeld,
                    TArtManager::instance().getImage(eImage::VFarmer)));
}
