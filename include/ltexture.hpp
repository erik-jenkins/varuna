#pragma once

#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class LTexture
{
public:
    LTexture();
    ~LTexture();

    void free();
    void render(SDL_Renderer* renderer,
                int x,
                int y,
                SDL_Rect* clip);

    void setColor(uint8_t red,
                  uint8_t green,
                  uint8_t blue);

    int getWidth();
    int getHeight();

    bool loadFromFile(SDL_Renderer*, std::string path);

private:
    SDL_Texture* texture;

    int width;
    int height;
};
