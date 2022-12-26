#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "assets/codes/RenderWindow.hpp"

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
    }

    window.CleanUp();
    SDL_Quit();

    return 0;
}