#include "render.hpp"

Render::Render(sf::RenderWindow& window, const float POINT_RADIUS) :
    POINT_RADIUS(POINT_RADIUS),
    window(window)
{
    float W = window.getView().getSize().x / 2.f;
    float H = window.getView().getSize().y / 2.f;

    transform.translate({W, H});
}

void Render::draw(const std::vector<Point>& points)
{
    for (const auto& point : points) {
        sf::CircleShape circle(POINT_RADIUS, 100);

        if (point.color) {
            circle.setFillColor(point.color.value());
        }

        sf::Vector2f position{
            point.coordinates.x,
            point.coordinates.y
        };

        circle.setPosition(transform.transformPoint(position));

        window.draw(circle);
    }
}