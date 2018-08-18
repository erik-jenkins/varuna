#ifndef LBUTTON_HPP
#define LBUTTON_HPP

#include <vector>

#include <SDL2/SDL.h>
#include "ltexture.hpp"

class LButton : public LTexture
{
public:
    LButton();

    void render(SDL_Renderer* renderer,
                double angle = 0.0,
                SDL_Point* center = nullptr,
                SDL_RendererFlip flip = SDL_FLIP_NONE);
    void setPosition(int x, int y);
    void handleEvent(SDL_Event* e);

    // button constants
    const int BUTTON_WIDTH  = 300;
    const int BUTTON_HEIGHT = 200;

private:

    enum LButtonSprite
    {
        BUTTON_SPRITE_MOUSE_OUT,
        BUTTON_SPRITE_MOUSE_OVER_MOTION,
        BUTTON_SPRITE_MOUSE_DOWN,
        BUTTON_SPRITE_MOUSE_UP,
        BUTTON_SPRITE_TOTAL,
    };

    SDL_Point position;
    LButtonSprite currentSprite;
    SDL_Rect buttonSprites[LButtonSprite::BUTTON_SPRITE_TOTAL];
};

#endif
