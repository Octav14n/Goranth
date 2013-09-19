#include "tgamemanager.h"

TGameManager::TGameManager() : selIsSelecting(false), spielfeld(TSpielfeld::instance())
{
    SDL_AddEventWatch(&TGameManager::SDL_EventWatchStatic, NULL);
}

void TGameManager::SDL_EventWatch(void *userdata, SDL_Event *event)
{
    (void)userdata; // Entferne die Warnung "unused-parameter".
    switch (event->type) {
    case SDL_MOUSEBUTTONDOWN:
        this->selIsSelecting = true;
        this->selXStart = event->motion.x;
        this->selYStart = event->motion.y;
        this->selXEnd = event->motion.x;
        this->selYEnd = event->motion.y;
    case SDL_MOUSEMOTION:
        if (this->selIsSelecting) {
            if (event->motion.x > this->selXStart) {
                this->selXEnd = event->motion.x;
            } else {
                this->selXStart = event->motion.x;
            }

            if (event->motion.y > this->selYStart) {
                this->selYEnd = event->motion.y;
            } else {
                this->selYStart = event->motion.y;
            }
        }
        break;
    case SDL_MOUSEBUTTONUP:
        this->selIsSelecting = false;
        if (event->button.button == SDL_BUTTON_LEFT) {
            this->spielfeld.setSelectedByArea(this->selXStart, this->selYStart, this->selXEnd - this->selXStart, this->selYEnd - this->selYStart);
        } else if (event->button.button == SDL_BUTTON_RIGHT) {
            this->spielfeld.setAction(event->button.x, event->button.y);
        }
    case SDL_KEYUP:
        if (event->key.keysym.scancode == SDL_SCANCODE_R) {
            this->spielfeld.cheat(TSpielfeld::CHEAT_ADD_FARMER, this->selXStart, this->selYStart);
        }
    default:
        break;
    }
}


void TGameManager::draw()
{
    this->spielfeld.Draw();
    if (this->selIsSelecting) {
        SDL_Rect rect = {this->selXStart, this->selYStart, this->selXEnd - this->selXStart, this->selYEnd - this->selYStart};
        TImage::drawRect(&rect, true, 127, 127, 255, 64);
        TImage::drawRect(&rect, false, 127,127, 255, 255);
    }
}

void TGameManager::update()
{
    this->spielfeld.Update();
}
