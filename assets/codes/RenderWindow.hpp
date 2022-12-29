#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "Entity.hpp"

using namespace std;

class RenderWindow
{
private:
    SDL_Window *window;
    SDL_Renderer *renderer;

public:
    RenderWindow(const char *p_title, int p_w, int p_h);
    SDL_Texture *LoadTexture(const char *p_filePath);
    void CleanUp();
    void Clear();
    void Render(Entity &p_entity);
    void Render(float p_x, float p_y, const char *p_text, TTF_Font *font, SDL_Color textColor);
    void RenderCenter(float p_x, float p_y, int screen_width, int screen_height, const char *p_text, TTF_Font *font, SDL_Color textColor);
    void Display();
};