#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Entity
{
private:
    double x, y;
    SDL_Rect currentFrame;
    SDL_Texture *tex;

public:
    Entity(float p_x, float p_y, SDL_Texture *p_tex);
    float GetX();
    float GetY();
    SDL_Texture *GetTexture();
    SDL_Rect GetCurrentFrame();
};
