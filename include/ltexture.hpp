#ifndef LTEXTURE_HPP
#define LTEXTURE_HPP

#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class LTexture
{
public:
    LTexture();
    ~LTexture();

    void free();
    void render(SDL_Renderer* renderer,
                int x,
                int y,
                SDL_Rect* clip = nullptr,
                double angle = 0.0,
                SDL_Point* center = nullptr,
                SDL_RendererFlip flip = SDL_FLIP_NONE);

    void setColor(uint8_t red,
                  uint8_t green,
                  uint8_t blue);

    void setBlendMode(SDL_BlendMode blendMode);
    void setAlpha(uint8_t alpha);

    int getWidth();
    int getHeight();

    bool loadFromFile(SDL_Renderer* renderer, std::string path);
    bool loadFromRenderedText(SDL_Renderer* renderer,
                              std::string text,
                              SDL_Color color,
                              TTF_Font* font);

protected:
    SDL_Texture* texture;

    int width;
    int height;
};

#endif
