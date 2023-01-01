#include "Projectile.hpp"

Projectile::Projectile(float xLeft, float xRight, SDL_Texture *texture)
{
    left = Entity(Vector2f(xLeft, 280), Vector2f(3, 3), texture);
    right = Entity(Vector2f(xRight, 280), Vector2f(3, 3), texture);
}
Projectile::Projectile(Entity pLeft, Entity pRight)
{
    left = pLeft;
    right = pRight;
}
Entity &Projectile::GetLeft() { return left; }
Entity &Projectile::GetRight() { return right; }
void Projectile::SetLeft(Entity pLeft)
{
    left = pLeft;
}
void Projectile::SetRight(Entity pRight)
{
    right = pRight;
}