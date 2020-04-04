#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "crosshair.h"

int main()
{
    crosshair *ch = new crosshair();

    sf::RenderWindow window(sf::VideoMode(600, 600), "!shooting practice!");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            ch->update();
        }

        window.clear(sf::Color::White);
        window.draw(*ch);
        window.display();
    }

    return 0;
}
