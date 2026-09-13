#include <SFML/Graphics.hpp>
#include <vector>
#include "render.hpp"
#include "particle.hpp"
#include "vec2.hpp"
#include "point.hpp"
#include <iostream>


const int WIDTH = 1200;
const int HEIGHT = 800;

int main()
{
   
    std::vector<Point> points;

    std::vector<Particle> particles(1);

    for (auto& particle : particles)
    {
        Particle part({580, 330});
        Point p{part.getPosition(), sf::Color::Yellow};

        points.push_back(p);
    }

    sf::Transform transform;
    transform.translate({WIDTH / 2, HEIGHT / 2});
    Render render(WIDTH, HEIGHT, transform);

    while (render.isOpen())
    {
        render.processEvents();
        render.clear();
        render.draw(points);
        render.display();
    }
}