#include "../include/ltexture.hpp"

LTexture::LTexture()
{
    texture = nullptr;
    width = 0;
    height = 0;
}

LTexture::~LTexture()
{
    free();
}

void LTexture::free()
{
    if (texture != nullptr)
    {
        SDL_DestroyTexture(texture);
        texture = nullptr;
        width = 0;
        height = 0;
    }
}

void LTexture::render(SDL_Renderer* renderer,
                      int x,
                      int y,
                      SDL_Rect* clip,
                      double angle,
                      SDL_Point* center,
                      SDL_RendererFlip flip)
{
    SDL_Rect renderQuad = {
        x,
        y,
        width,
        height
    };

    if (clip != nullptr)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopyEx(renderer,
                     texture,
                     clip,
                     &renderQuad,
                     angle,
                     center,
                     flip);
}

void LTexture::setColor(uint8_t red,
                        uint8_t green,
                        uint8_t blue)
{
    SDL_SetTextureColorMod(texture,
                           red,
                           green,
                           blue);
}

void LTexture::setBlendMode(SDL_BlendMode blendMode)
{
    SDL_SetTextureBlendMode(texture, blendMode);
}

void LTexture::setAlpha(uint8_t alpha)
{
    SDL_SetTextureAlphaMod(texture, alpha);
}

int LTexture::getWidth()
{
    return width;
}

int LTexture::getHeight()
{
    return height;
}

bool LTexture::loadFromFile(SDL_Renderer* renderer, std::string path)
{
    free();

    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr)
    {
        std::cout << "Could not load image at path: " << path.c_str();
        std::cout << std::endl;
        std::cout << "SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // color key image
    SDL_SetColorKey(loadedSurface,
                    SDL_TRUE,
                    SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
    newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (newTexture == nullptr)
    {
        std::cout << "Unable to create texture from " << path.c_str();
        std::cout << std::endl;
        std::cout << "SDL Error: " << SDL_GetError() << std::endl;
    }

    width  = loadedSurface->w;
    height = loadedSurface->h;

    SDL_FreeSurface(loadedSurface);
    texture = newTexture;
    return texture != nullptr;
}

bool LTexture::loadFromRenderedText(SDL_Renderer* renderer,
                                    std::string text,
                                    SDL_Color color,
                                    TTF_Font* font)
{
    free();

    // render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(font,
                                                    text.c_str(),
                                                    color);
    if (textSurface == nullptr)
    {
        std::cout << "Unable to render text surface! SDL_ttf Error: ";
        std::cout << TTF_GetError() << std::endl;
        return false;
    }

    // create texture from surface pixels
    texture = SDL_CreateTextureFromSurface(renderer,
                                           textSurface);
    if (texture == nullptr)
    {
        std::cout << "Unable to convert text surface to texture! SDL Error: ";
        std::cout << SDL_GetError() << std::endl;
        return false;
    }

    width = textSurface->w;
    height = textSurface->h;

    SDL_FreeSurface(textSurface);
    return texture != nullptr;
}
