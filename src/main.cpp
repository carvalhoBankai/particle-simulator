#include <SFML/Graphics.hpp>
#include <vector>
#include "render.hpp"

int main()
{
   
    std::vector<sf::Vector2f> points{
        {100.f, 100.f},
        {200.f, 200.f},
        {300.f, 300.f},
        {400.f, 250.f}
    };

    Render render(800, 600);


    while (render.isOpen())
    {
        render.processEvents();
        render.clear();
        render.draw(points);
        render.display();
    }
}