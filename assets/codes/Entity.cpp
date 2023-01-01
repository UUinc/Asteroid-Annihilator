#include "Entity.hpp"

// Constructors
Entity::Entity() {}
Entity::Entity(Vector2f p_pos, SDL_Texture *p_tex)
    : position(p_pos), angle(0), tex(p_tex)
{
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = 32;
    currentFrame.h = 32;
    SDL_QueryTexture(p_tex, NULL, NULL, &currentFrame.w, &currentFrame.h);
}
Entity::Entity(Vector2f p_pos, float p_angle, SDL_Texture *p_tex)
    : position(p_pos), angle(p_angle), tex(p_tex)
{
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = 32;
    currentFrame.h = 32;
    SDL_QueryTexture(p_tex, NULL, NULL, &currentFrame.w, &currentFrame.h);
}
Entity::Entity(Vector2f p_pos, Vector2f p_scale, SDL_Texture *p_tex)
    : position(p_pos), angle(0), scale(p_scale), tex(p_tex)
{
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = 32;
    currentFrame.h = 32;
    SDL_QueryTexture(p_tex, NULL, NULL, &currentFrame.w, &currentFrame.h);
}
Entity::Entity(Vector2f p_pos, float p_angle, Vector2f p_scale, SDL_Texture *p_tex)
    : position(p_pos), angle(p_angle), scale(p_scale), tex(p_tex)
{
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = 32;
    currentFrame.h = 32;
    SDL_QueryTexture(p_tex, NULL, NULL, &currentFrame.w, &currentFrame.h);
}
// Getters
Vector2f Entity::GetPosition() { return position; }
float Entity::GetAngle() { return angle; }
Vector2f Entity::GetScale() { return scale; }
SDL_Texture *Entity::GetTexture() { return tex; }
SDL_Rect Entity::GetCurrentFrame() { return currentFrame; }
circle Entity::GetCenter() { return center; }
// Setters
void Entity::SetPosition(float x, float y)
{
    position.x = x;
    position.y = y;
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
void Entity::SetCenter(int x, int y, int r)
{
    center.x = x;
    center.y = y;
    center.r = r;
}

void Entity::Move(float x, float y)
{
    SetPosition(GetPosition().x + x, GetPosition().y + y);
}

void Entity::Move(Vector2f value)
{
    Move(value.x, value.y);
}

bool Entity::GetCollision(Entity *other)
{
    int dx, dy, rs;
    dx = position.x + center.x - (other->GetPosition().x + other->GetCenter().x);
    dy = position.y + center.y - (other->GetPosition().y + other->GetCenter().y);
    rs = center.r + other->GetCenter().r;
    dx *= dx;
    dy *= dy;
    rs *= rs;

    return dx + dy < rs;
}