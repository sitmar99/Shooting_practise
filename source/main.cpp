#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <vector>
#include <memory>

#include "entity.h"
#include "crosshair.h"

int main()
{
    std::vector<std::shared_ptr<Entity>> entities;
    entities.push_back(std::make_shared<Crosshair>("sprites/crosshair.png", 50.0, 512));

    sf::RenderWindow window(sf::VideoMode(), "!shooting practice!", sf::Style::Fullscreen);
    window.setMouseCursorVisible(false);
    window.setFramerateLimit(60);


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
            
            entities[0] -> update();
        }

        window.clear(sf::Color::White);
        window.draw(*entities[0]);
        window.display();
    }

    return 0;
}
