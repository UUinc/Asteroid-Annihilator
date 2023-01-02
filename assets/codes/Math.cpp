#include "Math.hpp"

int RandomInt(int min, int max)
{
    max = max + 1 - min;
    return std::rand() % max + min;
}