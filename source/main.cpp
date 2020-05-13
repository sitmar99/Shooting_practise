#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <vector>
#include <deque>
#include <memory>
#include <time.h>
#include <thread>
#include <pthread.h>
#include <iostream>

#include "entity.h"
#include "crosshair.h"
#include "target.h"

void addTarget(std::deque<std::shared_ptr<Entity>> &entities, int width, int height)
{
    int rnd = rand()%1000 + 1;
    if (rnd < 9)
    {
        int posX, posY;

        // switch (rnd)
        // {
        // case 1:
        // case 5:
        //     posX = -100;
        //     posY = height / (rand() % 100);
        //     break;
        // case 2:
        // case 6:
        //     posX = height + 100;
        //     posY = height / (rand() % 100);
        //     break;
        // case 3:
        // case 7:
        //     posY = -100;
        //     posX = width / (rand() % 100);
        //     break;
        // case 4:
        // case 8:
        //     posY = width + 100;
        //     posX = width / (rand() % 100);
        //     break;
        // }

        entities.push_front(std::make_shared<Target>(sf::Vector2f(width/2, height/2),"sprites/target.jpeg", 200.0, 800));
    }
}

void update(std::deque<std::shared_ptr<Entity>> &entities, int width, int height)
{
    for (auto ent = entities.begin(); ent != entities.end(); ent++)
    {
        sf::Vector2f pos = (*ent)->getSprite()->getPosition();

        if (pos.x < -200 || pos.x > width + 200 || pos.y < -200 || pos.y > height + 200)
        {
            entities.erase(ent);
        }
        else
            (*ent) -> update();
    }
}

int main()
{
    srand(time(NULL));
    int points = 0;
    int width = sf::VideoMode::getDesktopMode().width;
    int height = sf::VideoMode::getDesktopMode().height;

    std::deque<std::shared_ptr<Entity>> entities;
    entities.push_back(std::make_shared<Crosshair>("sprites/crosshair.png", 50.0, 512));

    sf::RenderWindow window(sf::VideoMode(), "!shooting practice!", sf::Style::Fullscreen);
    window.setMouseCursorVisible(false);
    window.setFramerateLimit(60);

    std::cout << "flaming" << std::endl;

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
                    case sf::Keyboard::R:
                        // static_cast<Crosshair*>(entities.back().get())->reload();
                        break;
                }
                case sf::Event::MouseButtonPressed:
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        Crosshair *ch = static_cast<Crosshair*>(entities.back().get());
                        if (ch->shootable())
                            {
                                // ch->decBulletsLeft();
                                // std::cout << ch->getBulletsLeft() << std::endl;
                                ch->setShootedTime(time(NULL));
                            }
                        auto iter_end = entities.end() - 1;
                        for (auto iter = entities.begin(); iter != iter_end; iter++)
                        {
                            if (static_cast<Target*>(iter->get())->getAimed())
                            {
                                points+=static_cast<Target*>(iter->get())->getPoints();
                                entities.erase(iter);
                            }
                        }
                    }
                    break;
            }
        }

        addTarget(entities, width, height);
        update(entities, width, height);

        // std::cout << entities.size() << std::endl;
        // std::cout << points << std::endl;

        window.clear(sf::Color::White);

        for (auto ent: entities)
            window.draw(*ent);

        // for (auto ent = entities.rbegin(); ent != entities.rend(); ent++)
        //     window.draw(*(*ent));
        window.display();
    }

    return 0;
}