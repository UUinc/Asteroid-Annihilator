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

    RenderWindow window("Title", 1280, 720);

    SDL_Texture *grassTexture = window.LoadTexture("assets/sprites/ground_grass_1.png");

    vector<Entity> entities = {Entity(Vector2f(100, 50), grassTexture),
                               Entity(Vector2f(132, 50), grassTexture),
                               Entity(Vector2f(164, 50), grassTexture),
                               Entity(Vector2f(196, 50), grassTexture),
                               Entity(Vector2f(228, 50), grassTexture)};

    entities.push_back(Entity(Vector2f(228, 100), grassTexture));

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
        for (Entity &e : entities)
        {
            window.Render(e);
        }
        window.Display();
    }

    window.CleanUp();
    SDL_Quit();

    return 0;
}