#ifndef RENDER_H_
#define RENDER_H_

#include <SFML/Graphics.hpp>
#include <string>

class Render {
    private:
        sf::RenderWindow window;
        int width;
        int heigth;

    public:
        Render(unsigned int width, unsigned int height);
        void draw(const std::vector<sf::Vector2f>& points);
        void clear();
        void display();
        bool isOpen();
        void processEvents();
};

#endif