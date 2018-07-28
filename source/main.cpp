#include <cmath>
#include <iostream>
#include <string>
#include <algorithm>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../include/ltexture.hpp"

#define max_num(x,y) ((x) >= (y)) ? (x) : (y)
#define min_num(x,y) ((x) <= (y)) ? (x) : (y)

const int WIDTH  = 600;
const int HEIGHT = 480;

bool init();
bool loadMedia();
void close();

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;

LTexture gBackgroundTexture;

SDL_Rect gSpriteClips[4];

int main()
{
    if (!init())
    {
        return 1;
    }

    if (!loadMedia())
    {
        return 1;
    }

    bool quit = false;
    SDL_Event event;

    uint8_t r = 255;
    uint8_t g = 255;
    uint8_t b = 255;

    while (!quit)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_q:
                    r += 4;
                    r = min_num(r, 255);
                    break;
                case SDLK_a:
                    r -= 4;
                    r = max_num(r, 0);
                    break;
                case SDLK_w:
                    g += 4;
                    g = min_num(g, 255);
                    break;
                case SDLK_s:
                    g -= 4;
                    g = max_num(g, 0);
                    break;
                case SDLK_e:
                    b += 4;
                    b = min_num(b, 255);
                    break;
                case SDLK_d:
                    b -= 4;
                    b = max_num(b, 0);
                    break;
                }
            }
        }

        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        gBackgroundTexture.setColor(r, g, b);
        gBackgroundTexture.render(gRenderer, 0, 0, nullptr);

        SDL_RenderPresent(gRenderer);
    }

    close();

    return 0;
}

bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not initialize! SDL Error: ";
        std::cout << SDL_GetError() << std::endl;
        return false;
    }

    // initialize window
    gWindow = SDL_CreateWindow("Varuna",
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               WIDTH,
                               HEIGHT,
                               SDL_WINDOW_SHOWN);
    if (gWindow == nullptr)
    {
        std::cout << "Window could not be created! SDL Error: ";
        std::cout << SDL_GetError() << std::endl;
        return false;
    }

    // initialize renderer
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == nullptr)
    {
        std::cout << "Could not initialize renderer! SDL Error: ";
        std::cout << SDL_GetError() << std::endl;
        return false;
    }

    int imageFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imageFlags) & imageFlags))
    {
        std::cout << "SDL_Image could not initialize! SDL_image Error: ";
        std::cout << IMG_GetError() << std::endl;
    }

    return true;
}

bool loadMedia()
{
    bool success = true;

    success = gBackgroundTexture.loadFromFile(gRenderer, "assets/png/background.png");

    return success;
}

void close()
{
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    IMG_Quit();
    SDL_Quit();
    return;
}
