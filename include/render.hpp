#ifndef RENDER_H_
#define RENDER_H_

#include <SFML/Graphics.hpp>
#include <string>
#include "vec2.hpp"
#include "point.hpp"
#include <optional>

class Render {
    private:
        sf::RenderWindow window;
        int width;
        int heigth;
        std::optional<sf::Transform> transformation;

    public:
        Render(unsigned int width, unsigned int height, sf::Transform transformation);
        void draw(const std::vector<Point>& points);
        void clear();
        void display();
        bool isOpen();
        void processEvents();
};

#endif