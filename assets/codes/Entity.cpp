#include "Entity.hpp"

// Constructors
Entity::Entity(Vector2f p_pos, SDL_Texture *p_tex)
    : pos(p_pos), angle(0), tex(p_tex)
{
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = 32;
    currentFrame.h = 32;
    SDL_QueryTexture(p_tex, NULL, NULL, &currentFrame.w, &currentFrame.h);
}
Entity::Entity(Vector2f p_pos, float p_angle, SDL_Texture *p_tex)
    : pos(p_pos), angle(p_angle), tex(p_tex)
{
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = 32;
    currentFrame.h = 32;
    SDL_QueryTexture(p_tex, NULL, NULL, &currentFrame.w, &currentFrame.h);
}
Entity::Entity(Vector2f p_pos, Vector2f p_scale, SDL_Texture *p_tex)
    : pos(p_pos), angle(0), scale(p_scale), tex(p_tex)
{
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = 32;
    currentFrame.h = 32;
    SDL_QueryTexture(p_tex, NULL, NULL, &currentFrame.w, &currentFrame.h);
}
Entity::Entity(Vector2f p_pos, float p_angle, Vector2f p_scale, SDL_Texture *p_tex)
    : pos(p_pos), angle(p_angle), scale(p_scale), tex(p_tex)
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