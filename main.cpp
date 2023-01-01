#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <vector>

#include "assets/codes/RenderWindow.hpp"
#include "assets/codes/Entity.hpp"

using namespace std;

void Init()
{
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

int main(int argc, char *argv[])
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

    Entity background = Entity(Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), Vector2f(6, 6), backgroundTexture);

    Entity spaceship = Entity(Vector2f(SCREEN_WIDTH / 2 - 16, 300), Vector2f(3, 3), spaceshipTexture);
    Entity projectileLeft = Entity(Vector2f(SCREEN_WIDTH / 2 - 21, 280), Vector2f(3, 3), projectileTexture);
    Entity projectileRight = Entity(Vector2f(SCREEN_WIDTH / 2 + 5, 280), Vector2f(3, 3), projectileTexture);

    Entity asteroidLarge = Entity(Vector2f(100, 50), Vector2f(3, 3), asteroidLargeTexture);
    Entity asteroidMedium = Entity(Vector2f(200, 50), Vector2f(3, 3), asteroidMediumTexture);
    Entity asteroidSmall = Entity(Vector2f(308, 250), Vector2f(3, 3), asteroidSmallTexture);

    // Variables
    Vector2f movement;
    float movementSpeed = 5;

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
                    /* code */
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
                    /* code */
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
            if (spaceship.GetPos().x > 25)
            {
                spaceship.Move(movement);
            }
        }
        if (movement.x > 0)
        {
            if (spaceship.GetPos().x < SCREEN_WIDTH - 40)
            {
                spaceship.Move(movement);
            }
        }

        window.Render(spaceship);
        window.Render(projectileLeft);
        window.Render(projectileRight);
        window.Render(asteroidLarge);
        window.Render(asteroidMedium);
        window.Render(asteroidSmall);
        window.Display();
    }

    Mix_HaltMusic();
    Mix_FreeMusic(music);
    window.CleanUp();
    Quit();

    return 0;
}