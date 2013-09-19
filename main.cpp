#include <SDL2/SDL.h>
#include "tgamemanager.h"

int main()
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);
    atexit(SDL_Quit);
    SDL_CreateWindowAndRenderer(640, 480, SDL_WINDOW_FULLSCREEN_DESKTOP & 0, &window, &renderer);
    if (window == NULL || renderer == NULL) {
        printf("Couldn't create Window or Renderer: %s\n", SDL_GetError());
        return 0;
    }
    srand((unsigned) time(NULL));

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    TImage::Init(window, renderer);
    TGameManager &game = TGameManager::instance();
    game.Init(renderer);

    bool running = true;
    while (running) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_MOUSEMOTION:
            case SDL_MOUSEBUTTONDOWN:
            case SDL_WINDOWEVENT:
            case SDL_MOUSEBUTTONUP:
                break;
            case SDL_KEYDOWN:
                //printf("Event: Key: %i\n", event.key.keysym.scancode);
                switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    running = false;
                    break;
                default:
                    break;
                }
                break;
            case SDL_QUIT:
                printf("Event: Quit: %i\n", event.quit.timestamp);
                running = false;
                break;
                break;
            default:
                printf("Event: Unkown: %i\n", event.type);
                break;
            }
        }

        game.update();
        game.draw();

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    printf("Ende\n");
    return 0;
}
