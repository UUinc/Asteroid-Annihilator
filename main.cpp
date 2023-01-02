#include <SDL2/SDL_main.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <vector>

#include "assets/codes/RenderWindow.hpp"
#include "assets/codes/Entity.hpp"
#include "assets/codes/Projectile.hpp"
#include "assets/codes/Shapes.hpp"
#include "assets/codes/Asteroid.hpp"

using namespace std;

void Init()
{
    std::srand(std::time(nullptr));

    if (SDL_Init(SDL_INIT_VIDEO) > 0)
    {
        cout << "SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << endl;
    }

    if (!IMG_Init(IMG_INIT_PNG))
    {
        cout << "IMG_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << endl;
    }

    if (!Mix_Init(MIX_INIT_MP3 | MIX_INIT_OPUS | MIX_INIT_OGG))
    {
        cout << "Mix_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << endl;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 6, 4096) == -1)
    {
        cout << "Mix_OpenAudio HAS FAILED. SDL_ERROR: " << SDL_GetError() << endl;
    }
}

void Quit()
{
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

int SDL_main(int argc, char *argv[])
{
    Init();

    RenderWindow window("Asteroid Annihilator", SCREEN_WIDTH, SCREEN_HEIGHT);

    // MUSIC
    Mix_Music *music = Mix_LoadMUS("assets/sounds/music/SpaceRiddle.ogg");
    Mix_VolumeMusic(10);
    Mix_PlayMusic(music, 0);

    // Background
    SDL_Texture *backgroundTexture = window.LoadTexture("assets/sprites/background.png");
    // Spaceship
    SDL_Texture *spaceshipTexture = window.LoadTexture("assets/sprites/spaceship.png");
    SDL_Texture *projectileTexture = window.LoadTexture("assets/sprites/projectile.png");
    // Asteroids
    SDL_Texture *asteroidLargeTexture = window.LoadTexture("assets/sprites/asteroid_large.png");
    SDL_Texture *asteroidMediumTexture = window.LoadTexture("assets/sprites/asteroid_medium.png");
    SDL_Texture *asteroidSmallTexture = window.LoadTexture("assets/sprites/asteroid_small.png");

    Entity background = Entity(Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 20), Vector2f(6, 6), backgroundTexture);

    Entity spaceship = Entity(Vector2f(SCREEN_WIDTH / 2 - 16, 300), Vector2f(3, 3), spaceshipTexture);
    spaceship.SetCenter(16, 16, 22);
    vector<Projectile> projectiles;

    vector<Entity> asteroids;
    asteroids.push_back(RandomAsteroid(asteroidLargeTexture, asteroidMediumTexture, asteroidSmallTexture));

    // Variables
    Vector2f movement;
    float movementSpeed = 5;

    bool projectileLaunch = true;
    float projectileSpeed = 3;

    float asteroidSpeed = .5;

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
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_UP:
                    if (!projectileLaunch)
                        break;
                    projectiles.push_back(Projectile(spaceship.GetPosition().x - 5, spaceship.GetPosition().x + 21, projectileTexture));
                    projectileLaunch = false;
                    break;
                case SDLK_LEFT:
                case SDLK_a:
                    movement.x = -movementSpeed;
                    break;
                case SDLK_RIGHT:
                case SDLK_d:
                    movement.x = movementSpeed;
                    break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym)
                {
                case SDLK_UP:
                    projectileLaunch = true;
                    break;
                case SDLK_LEFT:
                case SDLK_a:
                    movement.x = 0;
                    break;
                case SDLK_RIGHT:
                case SDLK_d:
                    movement.x = 0;
                    break;
                }
                break;
            }
        }

        window.Clear();
        window.Render(background);

        // Spaceship movement
        if (movement.x < 0)
        {
            if (spaceship.GetPosition().x > 25)
            {
                spaceship.Move(movement);
            }
        }
        if (movement.x > 0)
        {
            if (spaceship.GetPosition().x < SCREEN_WIDTH - 40)
            {
                spaceship.Move(movement);
            }
        }

        // Projectile Movement
        for (int i = 0; i < projectiles.size(); i++)
        {
            // if projectile is outside of the screen wipe it
            if (projectiles[i].GetLeft().GetPosition().y < 0)
            {
                projectiles.erase(projectiles.begin() + i);
            }
            else
            {
                projectiles[i].GetLeft().Move(Vector2f(0, -projectileSpeed));
                projectiles[i].GetRight().Move(Vector2f(0, -projectileSpeed));

                window.Render(projectiles[i].GetLeft());
                window.Render(projectiles[i].GetRight());
            }

            for (int j = 0; j < asteroids.size(); j++)
            {
                if (projectiles[i].GetLeft().GetCollision(&asteroids[j]) || projectiles[i].GetRight().GetCollision(&asteroids[j]))
                {
                    switch (asteroids[j].GetCenter().r)
                    {
                    case 15:
                        cout << "Collision small!" << endl;
                        break;
                    case 38:
                        cout << "Collision medium!" << endl;
                        break;
                    case 46:
                        cout << "Collision large!" << endl;
                        break;
                    }

                    projectiles.erase(projectiles.begin() + i);
                    asteroids.erase(asteroids.begin() + j);

                    // instantiate new asteroid
                    asteroids.push_back(RandomAsteroid(asteroidLargeTexture, asteroidMediumTexture, asteroidSmallTexture));

                    // add speed to asteroids
                    asteroidSpeed += .2;
                }
            }
        }

        window.Render(spaceship);

        // Asteroids
        for (int i = 0; i < asteroids.size(); i++)
        {
            if (asteroids[i].GetCollision(&spaceship))
            {
                cout << "Game over" << endl;
                gameRunning = false;
                break;
            }

            if (asteroids[i].GetPosition().y > 410)
            {
                asteroids.erase(asteroids.begin() + i);
                // instantiate new asteroid
                asteroids.push_back(RandomAsteroid(asteroidLargeTexture, asteroidMediumTexture, asteroidSmallTexture));

                if (asteroidSpeed >= 1.2)
                {
                    // subs speed to asteroids
                    asteroidSpeed -= .2;
                }
            }
            else
            {
                asteroids[i].Move(Vector2f(0, asteroidSpeed));
                window.Render(asteroids[i]);
            }
        }

        window.Display();
    }

    Mix_HaltMusic();
    Mix_FreeMusic(music);
    window.CleanUp();
    Quit();

    return 0;
}