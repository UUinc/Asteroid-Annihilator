#include "Entity.hpp"

Entity::Entity(float p_x, float p_y, SDL_Texture *p_tex)
    : x(p_x), y(p_y), tex(p_tex)
{
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = 32;
    currentFrame.h = 32;
}

float Entity::GetX() { return x; }
float Entity::GetY() { return y; }
SDL_Texture *Entity::GetTexture() { return tex; }
SDL_Rect Entity::GetCurrentFrame() { return currentFrame; }