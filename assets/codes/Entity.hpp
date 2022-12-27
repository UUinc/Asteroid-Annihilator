#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Math.hpp"

class Entity
{
private:
    Vector2f pos;
    SDL_Rect currentFrame;
    SDL_Texture *tex;

public:
    Entity(Vector2f p_pos, SDL_Texture *p_tex);
    Vector2f GetPos();
    SDL_Texture *GetTexture();
    SDL_Rect GetCurrentFrame();
};
