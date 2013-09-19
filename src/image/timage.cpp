#include "timage.h"

SDL_Window *TImage::mainWindow = NULL;
SDL_Renderer *TImage::renderer = NULL;

TImage::TImage(const char *file, SDL_Renderer *renderer)
{
    SDL_assert_paranoid(TImage::mainWindow != NULL);
    if (renderer == NULL) {
        renderer = TImage::renderer;
    }
    this->renderer = renderer;
    this->img = IMG_LoadTexture(this->renderer, file);
    if (this->img == NULL) {
        SDL_ShowSimpleMessageBox(0, "Image Error", SDL_GetError(), TImage::mainWindow);
    }
    SDL_assert_release(this->img != NULL);
    SDL_QueryTexture(this->img, NULL, NULL, &this->w, &this->h);
}

void TImage::Draw(int x, int y, float angle) const {
    SDL_assert_paranoid(this->renderer != NULL);
    SDL_assert_paranoid(this->img != NULL);
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = this->w;
    r.h = this->h;
    try {
        SDL_RenderCopyEx(this->renderer, this->img, NULL, &r, angle, NULL, SDL_FLIP_NONE);
    } catch (...) {
        SDL_ShowSimpleMessageBox(0, "", SDL_GetError(), TImage::mainWindow);
    }
}

void TImage::Init(SDL_Window *win, SDL_Renderer *renderer) {
    TImage::mainWindow = win;
    TImage::renderer = renderer;
}
