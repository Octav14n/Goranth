#include "tspielfeld.h"

TSpielfeld::TSpielfeld() : selected(NULL), scrollX(0), scrollY(0)
{
    this->addWorld(true);
}

void TSpielfeld::Update() {
    for(std::list<TWorld*>::iterator i=this->worlds.begin(); i != this->worlds.end(); i++) {
        (static_cast<TWorld*>(*i))->update();
    }
}

void TSpielfeld::Draw() {
    this->activeWorld->draw(this->scrollX, this->scrollY);
}

void TSpielfeld::addWorld(bool setActive)
{
    TWorld *world = new TWorld(this);
    this->worlds.push_back(world);
    if (setActive) {
        this->activeWorld = world;
    }
}

void TSpielfeld::resetSelection()
{
    if (!this->selected) {return;}
    for(std::weak_ptr<TVec> i : *this->selected) {
        std::shared_ptr<TVec> vec = i.lock();
        if (vec) {
            vec->setSelected(false);
        }
    }
    this->selected.reset();
}

void TSpielfeld::notifySelected() const
{
    if (!this->selected) {return;}
    for(std::weak_ptr<TVec> i : *this->selected) {
        std::shared_ptr<TVec> vec = i.lock();
        if (vec) {
            vec->setSelected(true);
        }
    }
}

void TSpielfeld::setSelectedByArea(int x, int y, int xLength, int yLength)
{
    this->resetSelection();
    this->selected = this->activeWorld->getVecFromRect(x + scrollX, y + scrollY, xLength, yLength);
    printf("Selected %ld items.\n", (this->selected == NULL) ? 0 : this->selected->size());
    this->notifySelected();
}

void TSpielfeld::setAction(int x, int y)
{
    if (this->selected == NULL) {return;}
    for(std::weak_ptr<TVec> i : *this->selected) {
        std::shared_ptr<TVec> vec = i.lock();
        if (vec) {
            vec->setZiel(x + scrollX, y + scrollY);
        }
    }
}

void TSpielfeld::cheat(cheats cheat, int x, int y)
{
    (void)x;
    (void)y;
    switch (cheat) {
    case CHEAT_ADD_FARMER:
        //this->activeWorld->addVec(std::shared_ptr<TVec>(new TVec(x, y, eVec::Art::Farmer, this->activeWorld)));
        //break;
    default:
        printf("Todo: Implement cheat %i", static_cast<int>(cheat));
        break;
    }
}
