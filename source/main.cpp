#include <iostream>

#include <SDL2/SDL.h>

bool init();
bool loadMedia();
void close();

SDL_Window* gWindow = nullptr;
SDL_Surface* gScreenSurface = nullptr;
SDL_Surface* gXOut = nullptr;

int main(int argc, char* argv[])
{
    if (!init())
    {
	return 1;
    }

    if (!loadMedia())
    {
	return 1;
    }

    SDL_BlitSurface(gXOut, nullptr, gScreenSurface, nullptr);
    SDL_UpdateWindowSurface(gWindow);

    bool quit = false;
    SDL_Event event;
    while (!quit)
    {
	while (SDL_PollEvent(&event) != 0)
	{
	    if (event.type == SDL_QUIT)
	    {
		quit = true;
	    }
	}
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

    
    gWindow = SDL_CreateWindow("Varuna",
			      SDL_WINDOWPOS_UNDEFINED,
			      SDL_WINDOWPOS_UNDEFINED,
			      800,
			      600,
			      SDL_WINDOW_SHOWN);
    if (gWindow == nullptr)
    {
	std::cout << "Window could not be created! SDL Error: ";
	std::cout << SDL_GetError() << std::endl;
	return false;
    }

    gScreenSurface = SDL_GetWindowSurface(gWindow);
    return true;
}

bool loadMedia()
{
    char bmp_path[] = "assets/bmp/x.bmp";
    gXOut = SDL_LoadBMP(bmp_path);
    if (gXOut == nullptr)
    {
	std::cout << "Unable to load bitmap! SDL Error: " << std::endl;
	std::cout << SDL_GetError() << std::endl;
    }
    return true;
}

void close()
{
    SDL_FreeSurface(gXOut);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
    return;
}
