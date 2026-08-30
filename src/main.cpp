#include <SFML/Graphics.hpp>
#include <vector>
#include "render.hpp"
#include "vec2.hpp"
#include <iostream>

int main()
{
   
    std::vector<Vec2> points{
        {100.f, 100.f},
        {200.f, 200.f},
        {300.f, 300.f},
        {400.f, 250.f}
    };

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