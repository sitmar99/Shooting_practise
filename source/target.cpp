#include "target.h"

void Target::update()
{
    getSprite()->setPosition(getSprite()->getPosition() + direction * speed);

    if (this->getSprite()->getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition())))
        this->aimed = true;
    else
        this->aimed = false;
        
}

Target::Target(sf::Vector2f pos, std::string spritePath, double nSize, int oSize) : Entity(pos, spritePath, nSize, oSize)
{
    this->getSprite()->setOrigin(oSize/2, oSize/2);

    srand(time(NULL));
    this->direction = sf::Vector2f(rand()%360 - 180, rand()%360 - 180);
    this->speed = rand()%3 + 1;
    this->points = 10 * speed;
    this->speed *= 0.01;
}

Target::~Target() { std::cout << "flaming" << std::endl; }