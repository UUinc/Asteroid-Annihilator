#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "assets/codes/RenderWindow.hpp"
#include "assets/codes/Entity.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) > 0)
    {
        cout << "SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << endl;
    }

    if (!IMG_Init(IMG_INIT_PNG))
    {
        cout << "IMG_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << endl;
    }

    RenderWindow window("Asteroid Annihilator", SCREEN_WIDTH, SCREEN_HEIGHT);

    // Background
    SDL_Texture *backgroundTexture = window.LoadTexture("assets/sprites/background.png");
    // Spaceship
    SDL_Texture *spaceshipTexture = window.LoadTexture("assets/sprites/spaceship.png");
    SDL_Texture *projectileTexture = window.LoadTexture("assets/sprites/projectile.png");
    // Asteroids
    SDL_Texture *asteroidLargeTexture = window.LoadTexture("assets/sprites/asteroid_large.png");
    SDL_Texture *asteroidMediumTexture = window.LoadTexture("assets/sprites/asteroid_medium.png");
    SDL_Texture *asteroidSmallTexture = window.LoadTexture("assets/sprites/asteroid_small.png");

    Entity background = Entity(Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), Vector2f(6, 6), backgroundTexture);

    Entity spaceship = Entity(Vector2f(SCREEN_WIDTH / 2 - 16, 300), Vector2f(3, 3), spaceshipTexture);
    Entity projectileLeft = Entity(Vector2f(SCREEN_WIDTH / 2 - 21, 280), Vector2f(3, 3), projectileTexture);
    Entity projectileRight = Entity(Vector2f(SCREEN_WIDTH / 2 + 5, 280), Vector2f(3, 3), projectileTexture);

    Entity asteroidLarge = Entity(Vector2f(100, 50), Vector2f(3, 3), asteroidLargeTexture);
    Entity asteroidMedium = Entity(Vector2f(200, 50), Vector2f(3, 3), asteroidMediumTexture);
    Entity asteroidSmall = Entity(Vector2f(308, 250), Vector2f(3, 3), asteroidSmallTexture);

    // Game Loop
    bool gameRunning = true;
    SDL_Event event;

    while (gameRunning)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                gameRunning = false;
                break;
            }
        }

        window.Clear();
        window.Render(background);
        window.Render(spaceship);
        window.Render(projectileLeft);
        window.Render(projectileRight);
        window.Render(asteroidLarge);
        window.Render(asteroidMedium);
        window.Render(asteroidSmall);
        window.Display();
    }

    window.CleanUp();
    SDL_Quit();

    return 0;
}