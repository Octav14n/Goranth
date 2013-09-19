#include "tvec.h"

TVec::TVec(int x, int y, const sVec::Art *type, std::weak_ptr<TBuilding> homeBuilding, TWorld *world) :
   x(x), y(y), xZiel(x), yZiel(y),
   angle(0), angleZiel(0),
   aktion(eVec::Action::Idle),
   selected(false),
   art(type),
   world(world),
   image(type->image),
   homeBuilding(homeBuilding)
{
    printf("Create: <TVec %i>%p\n", static_cast<int>(art->art), this);
}

void TVec::draw(int scrollX, int scrollY) const {
    if (this->selected) {
        TImage::drawRect(this->x + scrollX, this->y + scrollY, this->image->getWidth(), this->image->getHeight(), true, 0, 255, 0, 127);
        TImage::drawRect(this->x + scrollX, this->y + scrollY, this->image->getWidth(), this->image->getHeight(), false, 0, 255, 0);
    }
    this->image->Draw(this->x + scrollX, this->y + scrollY, this->angle);
}

Uint32 TVec::update() {
    printf("TVec::update!\n");

    switch (this->aktion) {
    case eVec::Action::Idle:
        if(!this->doIDLE()) {
            if (this->aktion == eVec::Action::Idle) {
                this->aktion = eVec::Action::Work;
                return 1;
            }
        }
        return 0;
        break;
    case eVec::Action::Rotate:
        if(!this->doROTATE()) {
            this->aktion = eVec::Action::Move;
        }
        return 1;
        break;
    case eVec::Action::Move:
        if(!this->doMOVE()) {
            this->aktion = eVec::Action::Work;
        }
        return 1;
        break;
    case eVec::Action::Work:
        if(this->doWORK() == 0) {
            this->aktion = eVec::Action::Idle;
            if (!isHome()) {
                returnHome();
            }
            return 0;
        }
        return this->nextWork;
        break;
    default:
        return 0;
        break;
    }
}

void TVec::setZiel(int x, int y)
{
    this->xZiel = x;
    this->yZiel = y;
    int a = (this->xZiel - this->x);
    int b = (this->yZiel - this->y);
    this->angleZiel = atan2(b, a) * 180 / M_PI;

    if (this->angleZiel < 0) {
        this->angleZiel = 360 + this->angleZiel;
    }
    this->aktion = eVec::Action::Rotate;
    this->world->addVec(std::weak_ptr<TVec>(this->shared_from_this()));
    this->world->update(this->shared_from_this());
}

void TVec::setZiel(std::shared_ptr<TBuilding> build)
{
    setZiel(build->getX() + build->width()/2, build->getY() + build->height() / 2);
}

bool TVec::doIDLE() {
    return true;
}

bool TVec::doROTATE() {
    if (this->angleZiel == this->angle) {
        return false;
    } else if (abs(this->angleZiel - this->angle) < this->art->rotateGes) {
        this->angle = this->angleZiel;
    } else if (this->angleZiel - this->angle > 180 || (this->angleZiel - this->angle > -180 && this->angleZiel - this->angle < 0)) {
        this->angle -= this->art->rotateGes;
        if (this->angle < 0) {
            this->angle = 360 + this->angle;
        }
    } else {
        this->angle += this->art->rotateGes;
        this->angle = fmod(this->angle, 360);
    }
    return true;
}

bool TVec::doMOVE() {
    if (abs(this->xZiel - this->x) > .25 && abs(this->yZiel - this->y) > .25) {
        this->x += this->cos(angle) * .25;
        this->y += this->sin(angle) * .25;
    } else {
        // Angekommen du bist.
        this->x = this->xZiel;
        this->y = this->yZiel;
        this->workBuilding = this->world->getBuildingFromPoint(this->x, this->y);
        if (this->workBuilding.expired()) {
            printf("Kein Gebaeude an [%i / %i]\n", static_cast<int>(this->x), static_cast<int>(this->y));
        }
        return false;
    }
    return true;
}

Uint32 TVec::doWORK() {
    std::shared_ptr<TBuilding> workBuilding = this->workBuilding.lock();
    if (!workBuilding) {
        return 0;
    }
    if (this->nextWork <= SDL_GetTicks()) {
        this->nextWork = workBuilding->doWORK(this->shared_from_this());
    }
    return nextWork;
}

void TVec::returnHome()
{
    setZiel(homeBuilding.lock());
}


void TVec::setWorking(std::weak_ptr<TBuilding> building)
{
    this->workBuilding = building;
    this->aktion = eVec::Action::Work;
    this->world->update(this->shared_from_this());
}

bool TVec::isHome() const
{
    std::shared_ptr<TBuilding> ptr = homeBuilding.lock();
    if (!ptr) {return false;}
    return isInRect(ptr->getX(), ptr->getY(), ptr->width(), ptr->height());
}
