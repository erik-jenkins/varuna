#include <iostream>
#include <string>
#include <sstream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "../include/ltexture.hpp"

const int WIDTH  = 600;
const int HEIGHT = 480;

bool init();
bool loadMedia();
void close();

SDL_Window*   gWindow   = nullptr;
SDL_Renderer* gRenderer = nullptr;

TTF_Font* gFont;
LTexture gResetTimeTexture;
LTexture gTimeTexture;

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
    Uint32 startTime = 0;
    std::stringstream timeText;
    SDL_Color color = {0, 0, 0, 255};

    while (!quit)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
            {
                startTime = SDL_GetTicks();
            }
        }

        timeText.str("");
        timeText << "Milliseconds since start time: " << SDL_GetTicks() - startTime;

        bool success = gTimeTexture.loadFromRenderedText(gRenderer,
                                                         timeText.str(),
                                                         color,
                                                         gFont);
        if (!success)
        {
            std::cout << "Failed to render font texture! SDL Error: ";
            std::cout << SDL_GetError() << std::endl;
        }

        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        gResetTimeTexture.render(gRenderer,
                                 (WIDTH - gResetTimeTexture.getWidth())/2,
                                 0);

        gTimeTexture.render(gRenderer,
                            (WIDTH - gTimeTexture.getWidth())/2,
                            (HEIGHT - gTimeTexture.getHeight())/2);

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
    gRenderer = SDL_CreateRenderer(gWindow,
                                   -1,
                                   SDL_RENDERER_ACCELERATED |
                                   SDL_RENDERER_PRESENTVSYNC);
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
        return false;
    }

    if (TTF_Init() == -1)
    {
        std::cout << "SDL_ttf could not initialize! SDL_ttf Error: ";
        std::cout << TTF_GetError() << std::endl;
        return false;
    }

    return true;
}

bool loadMedia()
{
    bool success = true;

    gFont = TTF_OpenFont("assets/ttf/lazy.ttf", 28);
    if (gFont == nullptr)
    {
        std::cout << "Error loading lazy.ttf! SDL_ttf Error: ";
        std::cout << TTF_GetError() << std::endl;
        return false;
    }

    SDL_Color color = {0, 0, 0, 255};
    gResetTimeTexture.loadFromRenderedText(gRenderer,
                                           "Press enter to reset start time",
                                           color,
                                           gFont);

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
