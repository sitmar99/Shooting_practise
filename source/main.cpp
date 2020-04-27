#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <vector>
#include <memory>
#include <iostream>

#include "entity.h"
#include "crosshair.h"
#include "target.h"

void update(std::vector<std::shared_ptr<Entity>> entities)
{
    for (auto ent : entities)
    {
        ent -> update();
    }
}

int main()
{
    std::vector<std::shared_ptr<Entity>> entities;
    entities.push_back(std::make_shared<Target>(sf::Vector2f(200,200),"sprites/target.jpeg", 250.0, 800));
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
                case sf::Event::MouseButtonPressed:
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                        std::cout << "strzel!" << std::endl;
                    break;
            }

            update(entities);
        }

        window.clear(sf::Color::White);
        for (auto ent : entities)
            window.draw(*ent);
        window.display();
    }

    return 0;
}