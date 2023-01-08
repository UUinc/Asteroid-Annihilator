#include <SDL2/SDL_main.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>

#include "assets/codes/RenderWindow.hpp"
#include "assets/codes/Entity.hpp"
#include "assets/codes/Projectile.hpp"
#include "assets/codes/Shapes.hpp"
#include "assets/codes/Asteroid.hpp"

using namespace std;

enum scene
{
    home,
    game,
    gameover
};

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

    if (TTF_Init() == -1)
    {
        cout << "TTF_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << endl;
    }
}

void Quit()
{
    TTF_Quit();
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

int SDL_main(int argc, char *argv[])
{
    Init();

    RenderWindow window("Asteroid Annihilator", SCREEN_WIDTH, SCREEN_HEIGHT);

    SDL_Color white = {255, 255, 255};
    SDL_Color black = {0, 0, 0};

    // Fonts
    TTF_Font *font16 = TTF_OpenFont("assets/fonts/Pixellari.ttf", 16);
    TTF_Font *font24 = TTF_OpenFont("assets/fonts/Pixellari.ttf", 24);
    TTF_Font *font32 = TTF_OpenFont("assets/fonts/Pixellari.ttf", 32);
    TTF_Font *font48 = TTF_OpenFont("assets/fonts/Pixellari.ttf", 48);
    TTF_Font *font64 = TTF_OpenFont("assets/fonts/Pixellari.ttf", 64);

    //--Sounds--
    // MUSIC
    Mix_Music *music = Mix_LoadMUS("assets/sounds/music/music.ogg");
    Mix_VolumeMusic(10);
    Mix_PlayMusic(music, -1);

    // SFX
    Mix_Chunk *clickSFX = Mix_LoadWAV("assets/sounds/sfx/click.ogg");
    Mix_Chunk *laserSFX = Mix_LoadWAV("assets/sounds/sfx/laser.ogg");
    Mix_Chunk *collisionSFX = Mix_LoadWAV("assets/sounds/sfx/explosion.ogg");
    Mix_Chunk *gameOverSFX = Mix_LoadWAV("assets/sounds/sfx/gameOver.ogg");
    Mix_Volume(2, 50);
    Mix_VolumeChunk(laserSFX, 70);
    Mix_VolumeChunk(collisionSFX, 70);

    //--Textures--
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

    // score
    int score = 0;

    // Game Loop
    bool gameRunning = true;
    SDL_Event event;

    scene state = scene::home;

    while (gameRunning)
    {
        switch (state)
        {
        case scene::home:
            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                case SDL_QUIT:
                    gameRunning = false;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                case SDL_KEYDOWN:
                    state = scene::game;
                    break;
                }
                window.Clear();
                window.Render(background);
                window.Render(120, SCREEN_HEIGHT / 2 - 48, "Asteroid Annihilator", font48, white);
                window.Render(240, SCREEN_HEIGHT / 2, "Yahya Lazrek", font24, white);
                window.Render(240, SCREEN_HEIGHT / 2 + 150, "press any key to play", font16, white);

                window.Display();
            }
            break;
        case scene::game:
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
                    case SDLK_w:
                        if (!projectileLaunch)
                            break;
                        Mix_PlayChannel(-1, laserSFX, 0);
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
                    case SDLK_w:
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

                        // Play collision sfx
                        Mix_PlayChannel(-1, collisionSFX, 0);

                        projectiles.erase(projectiles.begin() + i);
                        asteroids.erase(asteroids.begin() + j);

                        // instantiate new asteroid
                        asteroids.push_back(RandomAsteroid(asteroidLargeTexture, asteroidMediumTexture, asteroidSmallTexture));

                        // add speed to asteroids
                        movementSpeed += .1;
                        asteroidSpeed += .2;

                        // add score
                        score++;
                        cout << "score: " << score << endl;
                    }
                }
            }

            // Asteroids
            for (int i = 0; i < asteroids.size(); i++)
            {
                if (asteroids[i].GetCollision(&spaceship))
                {
                    cout << "Game over" << endl;
                    asteroids.erase(asteroids.begin() + i);
                    movementSpeed = 5;
                    asteroidSpeed = .5;
                    score = 0;
                    // Play collision sfx
                    Mix_PlayChannel(-1, collisionSFX, 0);
                    Mix_PlayChannel(-1, gameOverSFX, 0);

                    state = scene::gameover;
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
                        movementSpeed -= .1;
                        asteroidSpeed -= .2;
                    }
                }
                else
                {
                    asteroids[i].Move(Vector2f(0, asteroidSpeed));
                    window.Render(asteroids[i]);
                }
            }

            // UI
            char scoreTxt[20];
            sprintf(scoreTxt, "score: %d", score);

            window.Render(260, 10, scoreTxt, font32, white);
            window.Render(spaceship);

            window.Display();

            break;
        case scene::gameover:
            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                case SDL_QUIT:
                    gameRunning = false;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                case SDL_KEYDOWN:
                    state = scene::game;
                    // instantiate new asteroid
                    asteroids.push_back(RandomAsteroid(asteroidLargeTexture, asteroidMediumTexture, asteroidSmallTexture));
                    break;
                }
                // reset everything
                window.Clear();
                window.Render(background);
                window.Render(160, SCREEN_HEIGHT / 2 - 32, "Game Over", font64, white);
                window.Render(220, SCREEN_HEIGHT / 2 + 150, "press any key to play again", font16, white);

                window.Display();
            }
            break;
        }
    }

    Mix_HaltMusic();
    Mix_FreeMusic(music);
    Mix_FreeChunk(gameOverSFX);
    Mix_FreeChunk(collisionSFX);
    Mix_FreeChunk(laserSFX);
    Mix_FreeChunk(clickSFX);

    window.CleanUp();
    Quit();

    return 0;
}