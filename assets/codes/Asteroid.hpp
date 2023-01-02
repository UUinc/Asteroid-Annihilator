#pragma once

#include "Entity.hpp"
#include "Math.hpp"

Entity RandomAsteroid(SDL_Texture *asteroidLargeTexture, SDL_Texture *asteroidMediumTexture, SDL_Texture *asteroidSmallTexture)
{
    Entity asteroidLarge = Entity(Vector2f(280, -50), Vector2f(3, 3), asteroidLargeTexture);
    asteroidLarge.SetCenter(22, 16, 46);
    return asteroidLarge;
}
