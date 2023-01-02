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
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
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
    dst.x = p_entity.GetPosition().x + (p_entity.GetCurrentFrame().w - p_entity.GetCurrentFrame().w * p_entity.GetScale().x) / 2;
    dst.y = p_entity.GetPosition().y + (p_entity.GetCurrentFrame().h - p_entity.GetCurrentFrame().h * p_entity.GetScale().y) / 2;
    dst.w = p_entity.GetCurrentFrame().w * p_entity.GetScale().x;
    dst.h = p_entity.GetCurrentFrame().h * p_entity.GetScale().y;

    SDL_RenderCopyEx(renderer, p_entity.GetTexture(), &src, &dst, p_entity.GetAngle(), 0, SDL_FLIP_NONE);
}

void RenderWindow::Render(float p_x, float p_y, const char *p_text, TTF_Font *font, SDL_Color textColor)
{
    SDL_Surface *surfaceMessage = TTF_RenderText_Blended(font, p_text, textColor);
    SDL_Texture *message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    src.w = surfaceMessage->w;
    src.h = surfaceMessage->h;

    SDL_Rect dst;
    dst.x = p_x;
    dst.y = p_y;
    dst.w = src.w;
    dst.h = src.h;

    SDL_RenderCopy(renderer, message, &src, &dst);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(message);
}

void RenderWindow::RenderCenter(float p_x, float p_y, int screen_width, int screen_height, const char *p_text, TTF_Font *font, SDL_Color textColor)
{
    SDL_Surface *surfaceMessage = TTF_RenderText_Blended(font, p_text, textColor);
    SDL_Texture *message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    src.w = surfaceMessage->w;
    src.h = surfaceMessage->h;

    SDL_Rect dst;
    dst.x = screen_width / 2 - src.w / 2 + p_x;
    dst.y = screen_height / 2 - src.h / 2 + p_y;
    dst.w = src.w;
    dst.h = src.h;

    SDL_RenderCopy(renderer, message, &src, &dst);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(message);
}

void RenderWindow::Display()
{
    SDL_RenderPresent(renderer);
}

SDL_Renderer *RenderWindow::GetRenderer() { return renderer; }