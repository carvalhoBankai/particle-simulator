#ifndef RENDER_H_
#define RENDER_H_

#include <SFML/Graphics.hpp>
#include <string>
#include "vec2.hpp"
#include "point.hpp"
#include <optional>

class Render {
    private:
        sf::RenderWindow& window;
        sf::Transform transform;
        const float POINT_RADIUS;

    public:
        Render(sf::RenderWindow& window, const float POINT_RADIUS);
        void draw(const std::vector<Point>& points);
};

#endif