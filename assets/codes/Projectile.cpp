#include "Projectile.hpp"

Projectile::Projectile(float xLeft, float xRight, SDL_Texture *texture)
{
    left = Entity(Vector2f(xLeft, 280), Vector2f(3, 3), texture);
    left.SetCenter(8, 8, 8);
    right = Entity(Vector2f(xRight, 280), Vector2f(3, 3), texture);
    right.SetCenter(8, 8, 8);
}
Projectile::Projectile(Entity pLeft, Entity pRight)
{
    left = pLeft;
    left.SetCenter(8, 8, 8);
    right = pRight;
    right.SetCenter(8, 8, 8);
}
Entity &Projectile::GetLeft() { return left; }
Entity &Projectile::GetRight() { return right; }
void Projectile::SetLeft(Entity pLeft)
{
    left = pLeft;
    left.SetCenter(8, 8, 8);
}
void Projectile::SetRight(Entity pRight)
{
    right = pRight;
    right.SetCenter(8, 8, 8);
}