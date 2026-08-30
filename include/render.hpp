#ifndef RENDER_H_
#define RENDER_H_

#include <SFML/Graphics.hpp>
#include <string>
#include "vec2.hpp"

class Render {
    private:
        sf::RenderWindow window;
        int width;
        int heigth;

    public:
        Render(unsigned int width, unsigned int height);
        void draw(const std::vector<Vec2>& points);
        void clear();
        void display();
        bool isOpen();
        void processEvents();
};

#endif