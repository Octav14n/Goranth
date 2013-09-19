#ifndef TGAMEMANAGER_H
#define TGAMEMANAGER_H
#include <SDL2/SDL.h>
#include "src/generic/Macros.h"
#include "tspielfeld.h"

class TGameManager
{
    DEF_SINGLETON ( TGameManager )
private:
    bool selIsSelecting;
    int selXStart, selYStart, selXEnd, selYEnd;
    TSpielfeld &spielfeld;
    SDL_Renderer *renderer;
public:
    void draw();
    void update();

    void SDL_EventWatch(void *userdata, SDL_Event *event);
    static int SDL_EventWatchStatic(void *userdata, SDL_Event *event) {
        TGameManager::instance().SDL_EventWatch(userdata, event);
        return 0; // <-- Wird eh ignoriert laut docs...
    }

    void Init(SDL_Renderer *renderer) {
        TGameManager::instance().renderer = renderer;
    }
};

#endif // TGAMEMANAGER_H
