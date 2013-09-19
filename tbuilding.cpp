#include "tbuilding.h"

TBuilding::TBuilding(int x, int y, const sBuilding::Art *type, TWorld *world) :
    x(x),
    y(y),
    health(type->maxHealth),
    nextWork(0),
    //workVecs(type->workMaxVecs, nullptr),
    art(type),
    world(world)
{
    printf("Create: <TBuilding %i(\"%s\")>%p\n", static_cast<int>(type->art), type->name, this);
    std::shared_ptr<TBuilding> ptr(this);

    for (int i = 0; i < art->workMaxVecs; i++) {
        workVecs.push_back(std::shared_ptr<TVec>(new TVec(
                                                     this->x,
                                                     this->y,
                                                     TVecManager::instance().getVec(eVec::Art::Farmer),
                                                     std::weak_ptr<TBuilding>(ptr),
                                                     world)));
    }
    /*for (std::shared_ptr<TVec> vec : this->workVecs) {
        vec = std::shared_ptr<TVec>(new TVec(
                                        this->x,
                                        this->y,
                                        TVecManager::instance().getVec(eVec::Art::Farmer),
                                        world));
    }*/

    this->world->addBuilding(ptr);
    this->world->update(ptr);
}

Uint32 TBuilding::update() {
    if (this->isWorkable()) {
        return this->doWORK();
    }
    return 0;
}

void TBuilding::draw(int scrollX, int scrollY) const {
    this->art->image->Draw(this->x + scrollX, this->y + scrollY);
    if (this->art->maxHealth != 0) {
        float healthPercent = (float)this->health / this->art->maxHealth;
        int healthBar = static_cast<int>((this->width() - 4) * healthPercent);
        if (healthPercent >= .33) {
            TImage::drawRect(this->x + scrollX + 2, this->y + scrollY + 2, healthBar, 6, true, 127, 255, 127, 255);
        } else {
            TImage::drawRect(this->x + scrollX + 2, this->y + scrollY + 2, healthBar, 6, true, 255, 127, 127, 255);
        }
        TImage::drawRect(this->x + scrollX + 2, this->y + scrollY + 2, this->width() - 4, 6, false, 127, 255, 255);
    }
}


/*
 * -- Wird nicht genutzt (solange das Building nicht gedreht werden kann)
 * tbuilding.h:

    float Sign(fPoint p1, fPoint p2, fPoint p3)
    {
      return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
    }
    bool IsPointInTri(fPoint pt, fPoint v1, fPoint v2, fPoint v3);

 * tbuilding.cpp:

bool TBuilding::IsPointInTri(fPoint pt, fPoint v1, fPoint v2, fPoint v3)
{
  bool b1, b2, b3;

  b1 = Sign(pt, v1, v2) < 0.0f;
  b2 = Sign(pt, v2, v3) < 0.0f;
  b3 = Sign(pt, v3, v1) < 0.0f;

  return ((b1 == b2) && (b2 == b3));
}*/

bool TBuilding::isPointIn(int x, int y) const {
    return (this->x + this->width() > x && this->x < x) && (this->y + this->height() > y && this->y < y);
}

Uint32 TBuilding::doWORK(std::shared_ptr<TVec> vec)
{
    if (this->nextWork > SDL_GetTicks()) {
        return this->nextWork;
    }

    switch (this->art->workArt) {
    case eBuilding::Work::Feld:
        if (this->isWorkable(vec)) {
            this->health -= 5;
            this->nextWork = SDL_GetTicks() + this->art->workDelayMS;
            return this->nextWork;
        }
        break;
    case eBuilding::Work::Farm:
        this->nextWork += this->art->workDelayMS;

        printf("trying to send vehicle\n");

        for (std::shared_ptr<TVec> vec : this->workVecs) {
            if (vec->getAktion() == eVec::Action::Idle) {
                printf("found vehicle, searching buildings\n");
                std::shared_ptr<std::vector< std::weak_ptr<TBuilding> > > liste = this->world->getBuildingFromPoint(this->x, this->y, this->art->radius, vec);
                if (!liste->empty()) {
                    printf("found %lu buildings, calculating which one to send to\n", liste->size());
                    for (std::weak_ptr<TBuilding> i : *liste.get()) {
                        std::shared_ptr<TBuilding> wb = i.lock();
                        if (wb) {
                            vec->setZiel(wb);
                            printf("Send vehicle %p to Building %p\n", vec.get(), wb.get());
                            break;
                        }
                    }
                }
                break;
            }
        }

        return this->nextWork;
        break;
    default:
        break;
    }
    return 0;  // Es muss nicht mehr gearbeitet werden.
}

// Wird abgefragt um zu bestimmen ob ein Vec dieses Gebaeude besuchen kann.
bool TBuilding::isWorkable(std::shared_ptr<TVec> vec)
{
    switch(this->art->workArt) {
    case eBuilding::Work::Feld:
        if (vec && vec->getArt() == eVec::Art::Farmer) {
            return this->health > 1;
        } else {
            return false;
        }
        break;
    case eBuilding::Work::Farm:
        if (!vec) {
            return true;
        }
        return false;
        break;
    default:
        return false;
        break;
    }
}
