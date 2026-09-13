#include <SFML/Graphics.hpp>
#include <vector>
#include "render.hpp"
#include "particle.hpp"
#include "vec2.hpp"
#include "point.hpp"
#include <iostream>

int main()
{
   
    std::vector<Point> points;

    std::vector<Particle> particles(10);
    Vec2 force = {2, 2};
    int i = 1;
    for (auto& particle : particles)
    {
        particle.ApllyForce(force*i, 2);
        i++;
    }

    for (auto& particle : particles)
    {
        particle.ApllyForce(force*i, 2);
        i++;

        Point p{particle.getPosition(), sf::Color::Yellow};

        points.push_back(p);
    }

    Vec2 v1(30, 10);

    v1 = v1 * 3;

    std::cout << "v1 : (x, y)" << "(" << v1.x << ", " << v1.y << ")" << std::endl;

    Render render(800, 600);

    while (render.isOpen())
    {
        render.processEvents();
        render.clear();
        render.draw(points);
        render.display();
    }
}