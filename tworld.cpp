#include "tworld.h"

TWorld::TWorld(TSpielfeld *spielfeld)  : spielfeld(spielfeld)
{
    new TBuilding(rand() % 620, rand() % 460, TBuildingManager::instance().getBuilding(eBuilding::Art::Weizenfeld), this);
    new TBuilding(rand() % 620, rand() % 460, TBuildingManager::instance().getBuilding(eBuilding::Art::Weizenfarm), this);
    //addVec(std::shared_ptr<TVec>(new TVec(rand() % 620, rand() % 460, TVecManager::instance().getVec(eVec::Art::Farmer), this)));
}

void TWorld::draw(int scrollX, int scrollY) const
{
    for (std::shared_ptr<TBuilding> i : this->gebaeude) {
        i->draw(scrollX, scrollY);
    }
    for (std::weak_ptr<TVec> i : this->vehicle) {
        std::shared_ptr<TVec> vec = i.lock();
        if (vec) {
            vec->draw(scrollX, scrollY);
        }
    }
}

Uint32 TWorld::update()
{
    std::multiset<sUpdateables> updateList(this->updateables);
    for (sUpdateables updateable : updateList) {
        if (updateable.time > SDL_GetTicks()) {
            return updateable.time;
        }
        std::shared_ptr<iUpdateable> obj = updateable.obj.lock();
        if (obj) {
            this->updateables.erase(updateable);
            this->update(obj);
        }
    }
    return 0;
}

void TWorld::update(std::shared_ptr<iUpdateable> obj)
{
    Uint32 nextTime = obj->update();
    if (nextTime != 0) {
        printf("Added to updateQue: %u (%p)\n", nextTime, obj.get());
        this->addUpdateable(std::weak_ptr<iUpdateable>(obj), nextTime);
        printf("UpdateQue now looks like this:\n");
        for (sUpdateables updateable : this->updateables) {
            printf("\t{time: %u, obj: %p}\n", updateable.time, updateable.obj.lock().get());
        }
    }
}

std::shared_ptr<std::vector<std::weak_ptr<TVec> > > TWorld::getVecFromRect(int xStart, int yStart, int xEnd, int yEnd) const
{
    std::shared_ptr<std::vector<std::weak_ptr<TVec> > > vecList(new std::vector<std::weak_ptr<TVec> >);
    for (std::weak_ptr<TVec> i : this->vehicle) {
        std::shared_ptr<TVec> vec = i.lock();
        if (vec && vec->isInRect(xStart, yStart, xEnd, yEnd)) {
            vecList->push_back(i);
        }
    }
    if (vecList->empty()) {
        return NULL;
    } else {
        return vecList;
    }
}

std::weak_ptr<TBuilding> TWorld::getBuildingFromPoint(int x, int y) const
{
    for(std::shared_ptr<TBuilding> i : this->gebaeude) {
        if (i->isPointIn(x, y)) {
           return std::weak_ptr<TBuilding>(i);
        }
    }
    return std::weak_ptr<TBuilding>();
}

std::shared_ptr<std::vector<std::weak_ptr<TBuilding> > > TWorld::getBuildingFromPoint(int x, int y, int range, std::shared_ptr<TVec> vec) const
{
    x *= x;
    y *= y;
    range *= range; // Range quadrieren (um spaeter keine Wurzel aus a^2+b^2 ziehen zu muessen)
    std::shared_ptr<std::vector<std::weak_ptr<TBuilding> > > list(new std::vector<std::weak_ptr<TBuilding> >());

    for(std::shared_ptr<TBuilding> i : this->gebaeude) {
        if (i->getX() * i->getX() - x + i->getY() * i->getY() - y < range && // Distance
                (vec == NULL || i->isWorkable(vec))) {
            list->push_back(std::weak_ptr<TBuilding>(i));
        }
    }
    return list;
}

void TWorld::removeBuilding(std::shared_ptr<TBuilding> building)
{
    printf("Removed %lu Building from\n", this->gebaeude.erase(building));
    for (std::weak_ptr<TVec> vec : this->vehicle) {
        if (vec.expired()) {
            this->vehicle.erase(vec);
        }
    }
}

bool TWorld::addUpdateable(std::weak_ptr<iUpdateable> updateable, Uint32 time)
{
    this->updateables.insert(sUpdateables(time, updateable));
    return true;
}
