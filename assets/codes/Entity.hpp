#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Math.hpp"

class Entity
{
private:
    Vector2f pos;
    float angle;
    Vector2f scale = Vector2f(1, 1);
    SDL_Rect currentFrame;
    SDL_Texture *tex;

public:
    Entity(Vector2f p_pos, SDL_Texture *p_tex);
    Vector2f GetPos();
    void SetPos(float x, float y);
    float GetAngle();
    void SetAngle(float ang);
    Vector2f GetScale();
    void SetScale(float w, float h);
    SDL_Texture *GetTexture();
    SDL_Rect GetCurrentFrame();
};
