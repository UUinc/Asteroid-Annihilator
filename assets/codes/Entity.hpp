#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Math.hpp"

struct circle
{
    int x = 16;
    int y = 16;
    int r = 16;
};

class Entity
{
private:
    Vector2f position;
    float angle;
    Vector2f scale = Vector2f(1, 1);
    SDL_Rect currentFrame;
    SDL_Texture *tex;
    circle center;

public:
    Entity();
    Entity(Vector2f p_pos, SDL_Texture *p_tex);
    Entity(Vector2f p_pos, float p_angle, SDL_Texture *p_tex);
    Entity(Vector2f p_pos, Vector2f p_scale, SDL_Texture *p_tex);
    Entity(Vector2f p_pos, float p_angle, Vector2f p_scale, SDL_Texture *p_tex);
    Vector2f GetPosition();
    void SetPosition(float x, float y);
    float GetAngle();
    void SetAngle(float ang);
    Vector2f GetScale();
    void SetScale(float w, float h);
    SDL_Texture *GetTexture();
    SDL_Rect GetCurrentFrame();
    circle GetCenter();
    void SetCenter(int x, int y, int r);

    void Move(float x, float y);
    void Move(Vector2f value);

    bool GetCollision(Entity *other);
};
