#include "../include/lbutton.hpp"

LButton::LButton()
{
    position.x = 0;
    position.y = 0;

    currentSprite = LButtonSprite::BUTTON_SPRITE_MOUSE_OUT;

    buttonSprites[LButtonSprite::BUTTON_SPRITE_MOUSE_OUT].x = 0;
    buttonSprites[LButtonSprite::BUTTON_SPRITE_MOUSE_OUT].y = 0;
    buttonSprites[LButtonSprite::BUTTON_SPRITE_MOUSE_OUT].w = BUTTON_WIDTH;
    buttonSprites[LButtonSprite::BUTTON_SPRITE_MOUSE_OUT].h = BUTTON_HEIGHT;

    buttonSprites[LButtonSprite::BUTTON_SPRITE_MOUSE_OVER_MOTION].x = 0;
    buttonSprites[LButtonSprite::BUTTON_SPRITE_MOUSE_OVER_MOTION].y = BUTTON_HEIGHT;
    buttonSprites[LButtonSprite::BUTTON_SPRITE_MOUSE_OVER_MOTION].w = BUTTON_WIDTH;
    buttonSprites[LButtonSprite::BUTTON_SPRITE_MOUSE_OVER_MOTION].h = BUTTON_HEIGHT;

    buttonSprites[LButtonSprite::BUTTON_SPRITE_MOUSE_DOWN].x = 0;
    buttonSprites[LButtonSprite::BUTTON_SPRITE_MOUSE_DOWN].y = 2*BUTTON_HEIGHT;
    buttonSprites[LButtonSprite::BUTTON_SPRITE_MOUSE_DOWN].w = BUTTON_WIDTH;
    buttonSprites[LButtonSprite::BUTTON_SPRITE_MOUSE_DOWN].h = BUTTON_HEIGHT;

    buttonSprites[LButtonSprite::BUTTON_SPRITE_MOUSE_UP].x = 0;
    buttonSprites[LButtonSprite::BUTTON_SPRITE_MOUSE_UP].y = 3*BUTTON_HEIGHT;
    buttonSprites[LButtonSprite::BUTTON_SPRITE_MOUSE_UP].w = BUTTON_WIDTH;
    buttonSprites[LButtonSprite::BUTTON_SPRITE_MOUSE_UP].h = BUTTON_HEIGHT;
}

void LButton::setPosition(int x, int y)
{
    position.x = x;
    position.y = y;
}

void LButton::handleEvent(SDL_Event *e)
{
    if (e->type == SDL_MOUSEMOTION ||
        e->type == SDL_MOUSEBUTTONDOWN ||
        e->type == SDL_MOUSEBUTTONUP)
    {
        // get mouse position
        int x, y;
        SDL_GetMouseState(&x, &y);

        // check button boundaries
        bool inside = true;

        if (x < position.x)
        {
            inside = false;
        }

        if (x > position.x + BUTTON_WIDTH)
        {
            inside = false;
        }

        if (y < position.y)
        {
            inside = false;
        }

        if (y > position.y + BUTTON_HEIGHT)
        {
            inside = false;
        }

        if (!inside)
        {
            currentSprite = LButtonSprite::BUTTON_SPRITE_MOUSE_OUT;
        }
        else
        {
            switch (e->type)
            {
            case SDL_MOUSEMOTION:
                currentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                break;
            case SDL_MOUSEBUTTONDOWN:
                currentSprite = BUTTON_SPRITE_MOUSE_DOWN;
                break;
            case SDL_MOUSEBUTTONUP:
                currentSprite = BUTTON_SPRITE_MOUSE_UP;
                break;
            }
        }
    }
}

void LButton::render(SDL_Renderer* renderer,
                     double angle,
                     SDL_Point* center,
                     SDL_RendererFlip flip)
{
    SDL_Rect renderQuad = {
        position.x,
        position.y,
        BUTTON_WIDTH,
        BUTTON_HEIGHT,
    };

    SDL_RenderCopyEx(renderer,
                     texture,
                     &buttonSprites[currentSprite],
                     &renderQuad,
                     angle,
                     center,
                     flip);
}
