#pragma once

#include "Entity.hpp"

class Projectile
{
private:
    Entity left;
    Entity right;

public:
    Projectile(float, float, SDL_Texture *);
    Projectile(Entity, Entity);
    Entity &GetLeft();
    Entity &GetRight();
    void SetLeft(Entity);
    void SetRight(Entity);
};