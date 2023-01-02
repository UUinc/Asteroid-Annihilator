#include "Asteroid.hpp"

Entity RandomAsteroid(SDL_Texture *asteroidLargeTexture, SDL_Texture *asteroidMediumTexture, SDL_Texture *asteroidSmallTexture)
{
    int spawnPosition[5] = {46, 168, 292, 428, 564};

    Entity asteroidLarge = Entity(Vector2f(292, -50), Vector2f(3, 3), asteroidLargeTexture);
    asteroidLarge.SetCenter(22, 16, 46);
    Entity asteroidMedium = Entity(Vector2f(46, -50), Vector2f(3, 3), asteroidMediumTexture);
    asteroidMedium.SetCenter(22, 8, 38);
    Entity asteroidSmall = Entity(Vector2f(564, -50), Vector2f(3, 3), asteroidSmallTexture);
    asteroidSmall.SetCenter(14, 6, 15);

    int position = RandomInt(0, 4);
    switch (RandomInt(0, 2))
    {
    case 0:
        asteroidLarge.SetPosition(spawnPosition[position], -50);
        return asteroidLarge;
    case 1:
        asteroidMedium.SetPosition(spawnPosition[position], -50);
        return asteroidMedium;
    case 2:
        asteroidSmall.SetPosition(spawnPosition[position], -50);
        return asteroidSmall;
    }

    return asteroidLarge;
}