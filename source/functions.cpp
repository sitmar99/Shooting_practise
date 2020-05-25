#include "functions.h"

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
                    bool hit = false;
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
                            hit = true;
                        }
                    }

                    if (!hit)
                        points -= 100;
                }
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            return 0;
        }
        break;
    }
    return 1;
}

int HiScore()
{
    std::string score;
    std::fstream hiscore ("hiscore.txt");

    getline(hiscore, score);
    // hiscore >> score;
    hiscore.close();

    std::cout << score << std::endl;

    return 0;
}

int Menu(sf::Event event, std::deque<std::shared_ptr<Entity>> &menuEntities, sf::Sound &gunShoot)
{    
    switch (event.type)
    {
    case sf::Event::KeyPressed:
        switch (event.key.code)
        {
        case sf::Keyboard::Space:
            return 1;
            break;
        case sf::Keyboard::Escape:
            return -1;
            break;
        }
        break;

    case sf::Event::MouseButtonPressed:
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            gunShoot.play();
            for(auto ent = menuEntities.begin(); ent != menuEntities.end(); ent++)
            {
                auto option = static_cast<menuOption*>(ent->get());
                if (option->getAimed())
                {
                    return option->getID();
                }
            }
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            return -1;
        }
        break;
    }

    return 0;
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

void updateMenu(std::deque<std::shared_ptr<Entity>> &menuEntities)
{
    for (auto ent : menuEntities)
        ent->update();
}