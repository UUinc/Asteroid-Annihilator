#include "Entity.hpp"

Entity::Entity(Vector2f p_pos, SDL_Texture *p_tex)
    : pos(p_pos), tex(p_tex)
{
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = 32;
    currentFrame.h = 32;
    SDL_QueryTexture(p_tex, NULL, NULL, &currentFrame.w, &currentFrame.h);
}

// Getters
Vector2f Entity::GetPos() { return pos; }
float Entity::GetAngle() { return angle; }
Vector2f Entity::GetScale() { return scale; }
SDL_Texture *Entity::GetTexture() { return tex; }
SDL_Rect Entity::GetCurrentFrame() { return currentFrame; }
// Setters
void Entity::SetPos(float x, float y)
{
    pos.x = x;
    pos.y = y;
}
void Entity::SetAngle(float ang)
{
    angle = ang;
}
void Entity::SetScale(float w, float h)
{
    scale.x = w;
    scale.y = h;
}