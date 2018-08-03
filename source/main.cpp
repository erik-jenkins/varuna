#include <cmath>
#include <iostream>
#include <string>
#include <algorithm>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../include/ltexture.hpp"

const int WIDTH  = 600;
const int HEIGHT = 480;

bool init();
bool loadMedia();
void close();

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;

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

    uint8_t fadeInAlpha = 0;
    uint8_t fadeOutAlpha = 255;

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
                    if (fadeInAlpha + 4 > 255) {
                        fadeInAlpha = 255;
                    }
                    else {
                        fadeInAlpha += 4;
                    }

                    if (fadeOutAlpha - 4 < 0) {
                        fadeOutAlpha = 0;
                    }
                    else {
                        fadeOutAlpha -= 4;
                    }
                    break;

                case SDLK_a:
                    if (fadeOutAlpha + 4 > 255) {
                        fadeOutAlpha = 255;
                    }
                    else {
                        fadeOutAlpha += 4;
                    }

                    if (fadeInAlpha - 4 < 0) {
                        fadeInAlpha = 0;
                    }
                    else {
                        fadeInAlpha -= 4;
                    }
                    break;
                }
            }
        }

        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        gFadeIn.setAlpha(fadeInAlpha);
        gFadeOut.setAlpha(fadeOutAlpha);

        gFadeIn.render(gRenderer, 0, 0, nullptr);
        gFadeOut.render(gRenderer, 0, 0, nullptr);

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

    success = gFadeIn.loadFromFile(gRenderer, "assets/png/fadein.png");
    if (success) {
        gFadeIn.setBlendMode(SDL_BLENDMODE_BLEND);
    }

    success = gFadeOut.loadFromFile(gRenderer, "assets/png/fadeout.png");
    if (success) {
        gFadeOut.setBlendMode(SDL_BLENDMODE_BLEND);
    }

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
