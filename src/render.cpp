#include "render.hpp"
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <limits>

Render::Render(sf::RenderWindow& window, const float POINT_RADIUS) :
                                        POINT_RADIUS(POINT_RADIUS),
                                        window(window) {
    float W = window.getView().getSize().x / 2.f;
    float H = window.getView().getSize().y / 2.f;
    transform.translate({W, H});
}

void Render::draw(const std::vector<Point>& points) {
    float xmax = 0, ymax = 0, xmin = 0, ymin = 0;


    auto view = window.getView();

    const auto viewSize = window.getView().getSize();

    for(auto& point : points) {
        xmax = std::max(xmax, point.coordinates.x);
        xmin = std::min(xmin, point.coordinates.x);
        ymax = std::max(ymax, point.coordinates.y);
        ymin = std::min(ymin, point.coordinates.y);
    }

    float maxX = std::max (abs (xmin), abs(xmax));
    float maxY = std::max (abs(ymin), abs(ymax));
    float limitX = viewSize.x / 2.f - 2 * POINT_RADIUS;
    float limitY = viewSize.y / 2.f - 2 * POINT_RADIUS;


    float s = 1.0f;

    if ((maxX != 0 || maxY != 0) && (maxX > limitX || maxY > limitY)) {
        float sx = maxX == 0
            ? std::numeric_limits<float>::infinity()
            : limitX / maxX;

        float sy = maxY == 0
            ? std::numeric_limits<float>::infinity()
            : limitY / maxY;

        s = std::min(sx, sy);
    }

    for(auto& point : points) {
        sf::CircleShape circle(2.0f, 100);
        if (point.color) {
            circle.setFillColor(point.color.value());
        }

        sf::Vector2f position{point.coordinates.x, point.coordinates.y};
        circle.setPosition(transform.transformPoint(s * position));
        window.draw(circle);
    }
}