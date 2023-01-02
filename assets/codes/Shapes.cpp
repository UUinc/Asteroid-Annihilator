#include "Shapes.hpp"

void renderCircle(SDL_Renderer *renderer, int x, int y, int radius)
{
    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            int dx = radius - w;
            int dy = radius - h;
            if ((dx * dx + dy * dy) <= (radius * radius))
            {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
}
void renderCirclePerimeter(SDL_Renderer *renderer, int x, int y, int radius)
{
    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            int dx = radius - w;
            int dy = radius - h;
            if ((dx * dx + dy * dy) == (radius * radius))
            {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
}

void renderCirclePerimeterBresenham(SDL_Renderer *renderer, int x0, int y0, int radius)
{
    int x = radius;
    int y = 0;
    int decisionOver2 = 1 - x; // Decision criterion divided by 2 evaluated at x=r, y=0

    while (y <= x)
    {
        SDL_RenderDrawPoint(renderer, x + x0, y + y0);   // Octant 1
        SDL_RenderDrawPoint(renderer, y + x0, x + y0);   // Octant 2
        SDL_RenderDrawPoint(renderer, -x + x0, y + y0);  // Octant 4
        SDL_RenderDrawPoint(renderer, -y + x0, x + y0);  // Octant 3
        SDL_RenderDrawPoint(renderer, -x + x0, -y + y0); // Octant 5
        SDL_RenderDrawPoint(renderer, -y + x0, -x + y0); // Octant 6
        SDL_RenderDrawPoint(renderer, x + x0, -y + y0);  // Octant 8
        SDL_RenderDrawPoint(renderer, y + x0, -x + y0);  // Octant 7
        y++;
        if (decisionOver2 <= 0)
        {
            decisionOver2 += 2 * y + 1; // Change in decision criterion for y -> y+1
        }
        else
        {
            x--;
            decisionOver2 += 2 * (y - x) + 1; // Change for y -> y+1, x -> x-1
        }
    }
}

void ColliderRender(SDL_Renderer *renderer, Entity entity, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    renderCirclePerimeterBresenham(renderer, entity.GetPosition().x + entity.GetCenter().x - 8, entity.GetPosition().y + entity.GetCenter().y, entity.GetCenter().r);
}
void ColliderRender(SDL_Renderer *renderer, Entity entity)
{
    SDL_Color color = {255, 0, 0, 255};
    ColliderRender(renderer, entity, color);
}