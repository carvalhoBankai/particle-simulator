#include "render.hpp"

Render::Render(unsigned int width, unsigned int heigth) :
                                        width(width),
                                        heigth(heigth),
                                        window(sf::VideoMode({width, heigth}),"My SFML Window") {
}

void Render::draw(const std::vector<Point>& points) {

    for(auto& point : points) {
        sf::CircleShape circle(1.0f);
        if (point.color) {
            circle.setFillColor(point.color.value());
        }
        circle.setPosition({point.coordinates.x, point.coordinates.y});
        window.draw(circle);
    }
}

void Render::clear(){
    window.clear();
}

void Render::display(){
    window.display();
}

bool Render::isOpen()
{
    return window.isOpen();
}

void Render::processEvents()
{
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }
    }
}