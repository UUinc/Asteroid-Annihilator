#include "Entity.hpp"

Entity::Entity(Vector2f p_pos, SDL_Texture *p_tex)
    : pos(p_pos), tex(p_tex)
{
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = 32;
    currentFrame.h = 32;
}

Vector2f Entity::GetPos() { return pos; }
SDL_Texture *Entity::GetTexture() { return tex; }
SDL_Rect Entity::GetCurrentFrame() { return currentFrame; }