#ifndef TIMAGE_H
#define TIMAGE_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class TImage
{
private:
    int w, h;
    SDL_Texture *img = NULL;
    static SDL_Window *mainWindow;
    static SDL_Renderer *renderer;
public:
    TImage(const char *file, SDL_Renderer *renderer = NULL);
    void Draw(int x, int y, float angle = 0) const;
    static void Init(SDL_Window *win, SDL_Renderer *renderer);
    int getWidth() const{
        return this->w;
    }
    int getHeight() const{
        return this->h;
    }
    static void drawRect(int x, int y, int w, int h, bool filled = false, int r = 255, int g = 255, int b = 255, int a = 255) {
        SDL_Rect rect = {x, y, w, h};
        drawRect(&rect, filled, r, g, b, a);
    }
    static void drawRect(SDL_Rect *rect, bool filled = false, int r = 255, int g = 255, int b = 255, int a = 255) {
        Uint8 r1, g1, b1, a1;
        SDL_GetRenderDrawColor(TImage::renderer, &r1, &g1, &b1, &a1);
        SDL_SetRenderDrawColor(TImage::renderer, r, g, b, a);

        if (filled) {
            SDL_RenderFillRect(TImage::renderer, rect);
        } else {
            SDL_RenderDrawRect(TImage::renderer, rect);
        }

        SDL_SetRenderDrawColor(TImage::renderer, r1, g1, b1, a1);
    }
};

#endif // TIMAGE_H
