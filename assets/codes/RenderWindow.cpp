#include "RenderWindow.hpp"

RenderWindow::RenderWindow(const char *p_title, int p_w, int p_h)
    : window(NULL), renderer(NULL)
{
    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);

    if (window == NULL)
    {
        cout << "Window failed to init. Error: " << SDL_GetError() << endl;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

SDL_Texture *RenderWindow::LoadTexture(const char *p_filePath)
{
    SDL_Texture *texture = NULL;
    texture = IMG_LoadTexture(renderer, p_filePath);

    if (texture == NULL)
    {
        cout << "Failed to load texture. Error: " << SDL_GetError() << endl;
    }

    return texture;
}

void RenderWindow::CleanUp()
{
    SDL_DestroyWindow(window);
}

void RenderWindow::Clear()
{
    SDL_RenderClear(renderer);
}

void RenderWindow::Render(Entity &p_entity)
{
    SDL_Rect src;
    src.x = p_entity.GetCurrentFrame().x;
    src.y = p_entity.GetCurrentFrame().y;
    src.w = p_entity.GetCurrentFrame().w;
    src.h = p_entity.GetCurrentFrame().h;

    SDL_Rect dst;
    dst.x = p_entity.GetPos().x * 4;
    dst.y = p_entity.GetPos().y * 4;
    dst.w = p_entity.GetCurrentFrame().w * 4;
    dst.h = p_entity.GetCurrentFrame().h * 4;

    SDL_RenderCopy(renderer, p_entity.GetTexture(), &src, &dst);
}

void RenderWindow::Display()
{
    SDL_RenderPresent(renderer);
}