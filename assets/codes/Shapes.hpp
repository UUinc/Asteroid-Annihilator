#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Entity.hpp"

void renderCircle(SDL_Renderer *renderer, int x, int y, int radius);
void renderCirclePerimeter(SDL_Renderer *renderer, int x, int y, int radius);
void renderCirclePerimeterBresenham(SDL_Renderer *renderer, int x0, int y0, int radius);

void ColliderRender(SDL_Renderer *renderer, Entity entity, SDL_Color color);
void ColliderRender(SDL_Renderer *renderer, Entity entity);