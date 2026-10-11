#include <SFML/Graphics.hpp>
#include <vector>
#include "render.hpp"
#include "particle.hpp"
#include "vec2.hpp"
#include "point.hpp"
#include <iostream>
#include <random>



const float POINT_RADIUS = 2.0f;

int main()
{
   
   std::vector<Point> points;

std::mt19937 generator(std::random_device{}());
std::uniform_real_distribution<float> position(-1200.f, 1200.f);

std::vector<sf::Color> colors{
    sf::Color::Red,
    sf::Color::Green,
    sf::Color::Blue,
    sf::Color::Yellow,
    sf::Color::Cyan,
    sf::Color::Magenta,
    sf::Color::White
};

for (int i = 0; i < 50; ++i)
{
    points.push_back(Point{
        {position(generator), position(generator)},
        colors[i % colors.size()]
    });
}

    sf::RenderWindow window(
    sf::VideoMode({800, 800}),
    "Particle Simulation"
    );

    Render render(window, POINT_RADIUS);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear();
        render.draw(points);
        window.display();
    }
}