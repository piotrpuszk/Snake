#include "Maths.h"
#include <cmath>

float Maths::dot(sf::Vector2f v1, sf::Vector2f v2)
{
    return v1.x*v2.x + v1.y*v2.y;
}

float Maths::magnitude(sf::Vector2f v)
{
    return sqrtf(v.x*v.x + v.y*v.y);
}

sf::Vector2f Maths::round(sf::Vector2f v)
{
    v.x = roundf(v.x);
    v.y = roundf(v.y);

    return v;
}
