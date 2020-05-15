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
    int rnd = rand()%500 + 1;
    std::cout << rnd << std:: endl;
    if (rnd < 9)
    {
        int posX, posY;
        sf::Vector2f direction;
        double help = (rand() % 100) / 100.0;

        switch (rnd)
        {
        case 1:
        case 2:
            posX = -100;
            posY = height * help;
            help = posY - height/2;         //zmienna pomocnicza do losowania kierunku celu
            direction = sf::Vector2f(rand() % 180, (rand() % 90) * (-help / abs(help)));
            break;
        case 3:
        case 4:
            posX = width + 100;
            posY = height * help;
            help = posY - height/2;
            direction = sf::Vector2f(-rand() % 180, (rand() % 90) * (-help / abs(help)));
            break;
        case 5:
        case 6:
            posY = -100;
            posX = width * help;
            help = posY - width/2;
            direction = sf::Vector2f((rand() % 90) * (-help / abs(help)), rand() % 180);
            break;
        case 7:
        case 8:
            posY = height + 100;
            posX = width * help;
            help = posY - width/2;
            direction = sf::Vector2f((rand() % 90) * (-help / abs(help)), -rand() % 180);
            break;
        }

        entities.push_front(std::make_shared<Target>(direction, sf::Vector2f(posX, posY),"sprites&fonts/target.jpeg", 200.0, 800));
    }
}

void update(std::deque<std::shared_ptr<Entity>> &entities, int width, int height, int &points)
{
    for (auto ent = entities.begin(); ent != entities.end(); ent++)
    {
        sf::Vector2f pos = (*ent)->getSprite()->getPosition();

        if (pos.x < -200 || pos.x > width + 200 || pos.y < -200 || pos.y > height + 200)
        {
            points -= static_cast<Target*>(ent->get())->getPoints();
            entities.erase(ent--);
        }
        else
            (ent->get()) -> update();
    }
}

int main()
{
    srand(time(NULL));
    int points = 0;
    int width = sf::VideoMode::getDesktopMode().width;
    int height = sf::VideoMode::getDesktopMode().height;

    std::deque<std::shared_ptr<Entity>> entities;
    entities.push_back(std::make_shared<Crosshair>("sprites&fonts/crosshair.png", 50.0, 512));

    sf::Font font;
    font.loadFromFile("sprites&fonts/western.ttf");
    sf::Text text;
    text.setFont(font);
    text.setString("Points: 0");
    text.setCharacterSize(80);
    text.setFillColor(sf::Color::Black);
    text.setPosition(sf::Vector2f(10,height-90));

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
                            for (auto iter = entities.begin(); iter != entities.end(); iter++)
                            {
                                if (static_cast<Target*>(iter->get())->getAimed())
                                {
                                    points += static_cast<Target*>(iter->get())->getPoints();
                                    entities.erase(iter);
                                }
                            }
                            }
                    }
                    break;
            }
        }

        addTarget(entities, width, height);
        update(entities, width, height, points);

        window.clear(sf::Color::White);

        for (auto ent: entities)
            window.draw(*ent);
        
        text.setString("Points: " + std::to_string(points));
        window.draw(text);
        
        window.display();
    }

    return 0;
}