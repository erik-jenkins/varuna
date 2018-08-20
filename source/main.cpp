#include <chrono>
#include <iostream>
#include <string>
#include <sstream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "../include/ltexture.hpp"

const int WIDTH  = 600;
const int HEIGHT = 480;

typedef std::chrono::high_resolution_clock Clock;

bool init();
bool loadMedia();
void close();

SDL_Window*   gWindow   = nullptr;
SDL_Renderer* gRenderer = nullptr;

TTF_Font* gFont;
LTexture gFpsFont;

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

    // timing variables
    double dt = 0.01;
    double fps;

    auto currentTime = Clock::now();
    double accumulator = 0.0;

    int numFrames = 0;
    std::stringstream fpsStringStream;

    while (!quit)
    {
        // get times
        auto newTime = Clock::now();
        double frameTime = (double)std::chrono::duration_cast
            <std::chrono::milliseconds>(newTime - currentTime).count()/1.0e6f;
        if (frameTime > 0.25)
        {
            frameTime = 0.25;
        }
        currentTime = newTime;
        accumulator += frameTime;

        // calculate FPS
        fps = numFrames/(SDL_GetTicks()/1000.f);
        if (fps > 2000000)
        {
            fps = 0;
        }

        fpsStringStream.str("");
        fpsStringStream << "Average FPS: " << fps;
        gFpsFont.loadFromRenderedText(gRenderer,
                                      fpsStringStream.str(),
                                      {0, 0, 0, 255},
                                      gFont);

        // handle input
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        while (accumulator > dt)
        {
            // update(dt)
            accumulator -= dt;
        }

        const double alpha = accumulator/dt;

        // render(alpha)
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        gFpsFont.render(gRenderer,
                        10,
                        (HEIGHT-gFpsFont.getHeight()));

        SDL_RenderPresent(gRenderer);

        numFrames++;
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
