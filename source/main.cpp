#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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
#include "menuOption.h"

void addTarget(std::deque<std::shared_ptr<Entity>> &entities, int width, int height)
{
    int rnd = rand()%500 + 1;
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
            direction = sf::Vector2f(rand() % 180, (rand() % 45) * (-help / abs(help)));
            break;
        case 3:
        case 4:
            posX = width + 100;
            posY = height * help;
            help = posY - height/2;
            direction = sf::Vector2f(-rand() % 180, (rand() % 45) * (-help / abs(help)));
            break;
        case 5:
        case 6:
            posY = -100;
            posX = width * help;
            help = posY - width/2;
            direction = sf::Vector2f((rand() % 45) * (-help / abs(help)), rand() % 180);
            break;
        case 7:
        case 8:
            posY = height + 100;
            posX = width * help;
            help = posY - width/2;
            direction = sf::Vector2f((rand() % 45) * (-help / abs(help)), -rand() % 180);
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

        if (pos.x < -100 || pos.x > width + 100 || pos.y < -100 || pos.y > height + 100)
        {
            points -= static_cast<Target*>(ent->get())->getPoints();
            entities.erase(ent--);
        }
        else
            (ent->get()) -> update();
    }
}

    bool menu = true;

int Menu(sf::Event event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        switch (event.key.code)
        {
        case sf::Keyboard::Space:
            return 1;
            break;
        case sf::Keyboard::Escape:
            return -1;
            break;
        }
    }
    return 0;
}

void updateMenu(std::deque<std::shared_ptr<Entity>> &menuEntities)
{
    for (auto ent : menuEntities)
        ent->update();
}

void drawMenu(sf::RenderWindow &window, std::deque<std::shared_ptr<Entity>> &menuEntities)
{
    for (auto ent : menuEntities)
        window.draw(*ent);
}

void drawPoints(sf::RenderWindow &window, sf::Text text, int height, int width, int points, std::deque<std::shared_ptr<Entity>> &entities)
{
    text.setString("Points: " + std::to_string(points));
    text.setPosition(sf::Vector2f(10,height-90));
    window.draw(text);
    text.setString(std::to_string(static_cast<Crosshair*>(entities.back().get())->getBulletsLeft()));
    text.setPosition(sf::Vector2f(width - 50,height - 90));
    window.draw(text);

}

int Game(sf::Event event, std::deque<std::shared_ptr<Entity>> &entities, int &points, sf::Sound &gunShoot)
{
    switch(event.type)
    {
    case sf::Event::KeyPressed:
    {
        switch (event.key.code)
        {
        case sf::Keyboard::Escape:
            points = 0;
            return 0;
            break;
        case sf::Keyboard::R:
            // static_cast<Crosshair*>(entities.back().get())->reload();
            break;
        }
    }
    case sf::Event::MouseButtonPressed:
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            Crosshair *ch = static_cast<Crosshair*>(entities.back().get());
            if (ch->shootable())
                {
                    // ch->decBulletsLeft();
                    // std::cout << ch->getBulletsLeft() << std::endl;
                    gunShoot.play();
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
    return 1;
}

int main()
{
    srand(time(NULL));
    int option = 0;
    int points = 0;
    int width = sf::VideoMode::getDesktopMode().width;
    int height = sf::VideoMode::getDesktopMode().height;

    //Lista entities oraz dodanie celownika
    std::deque<std::shared_ptr<Entity>> entities;
    entities.push_back(std::make_shared<Crosshair>("sprites&fonts/crosshair.png", 50.0, 512));

    //Lista spritow menu
    std::deque<std::shared_ptr<Entity>> menuEntities;
    menuEntities.push_back(std::make_shared<menuOption>(sf::Vector2f(10,10), "sprites&fonts/play.png", sf::Vector2f(342, 214), sf::Vector2f(342, 214)));

    //Czcionki i tekst
    sf::Font font;
    font.loadFromFile("sprites&fonts/western.ttf");
    sf::Text text;
    text.setFont(font);
    text.setString("Points: 0");
    text.setCharacterSize(80);
    text.setFillColor(sf::Color::Black);

    //Dzwieki
    sf::SoundBuffer buffer;
    buffer.loadFromFile("sprites&fonts/gun_sound_shoot.wav");
    sf::Sound gunShoot;
    gunShoot.setBuffer(buffer);


    //Okno
    sf::RenderWindow window(sf::VideoMode(), "!shooting practice!", sf::Style::Fullscreen);
    window.setMouseCursorVisible(false);
    window.setFramerateLimit(60);

    sf::Event event;

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                break;
            }
            else
            {
                switch (option)
                {
                case -1:
                    window.close();
                    break;
                case 0:
                    option = Menu(event);
                    break;
                case 1:
                    option = Game(event, entities, points, gunShoot);
                    break;
                
                default:
                    break;
                }
            }
        }

        addTarget(entities, width, height);
        update(entities, width, height, points);

        window.clear(sf::Color::White);
        
        switch (option)
        {
        case 0:
            updateMenu(menuEntities);
            drawMenu(window, menuEntities);
            break;
        case 1:
            drawPoints(window, text, height, width, points, entities);
            break;
        }

        for (auto ent: entities)
            window.draw(*ent);

        window.display();
    }

    return 0;
}