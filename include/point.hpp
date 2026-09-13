#ifndef POINT_H_
#define POINT_H_

#include "vec2.hpp"
#include <optional>
#include <SFML/Graphics/Color.hpp>

struct Point
{
    Vec2 coordinates;
    std::optional<sf::Color> color;
};


#endif