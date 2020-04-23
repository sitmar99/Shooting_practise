#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "crosshair.h"

int main()
{
    crosshair *ch = new crosshair();

    sf::RenderWindow window(sf::VideoMode(), "!shooting practice!", sf::Style::Fullscreen);
    window.setMouseCursorVisible(false);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                {
                    switch (event.key.code)
                    {
                    case sf::Keyboard::Escape:
                        window.close();
                        break;
                    }
                }
            }
            
            ch->update();
        }

        window.clear(sf::Color::White);
        window.draw(*ch);
        window.display();
    }

    return 0;
}
