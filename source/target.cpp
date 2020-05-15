#include "target.h"

void Target::update()
{
    getSprite()->move(direction * speed);

    if (this->getSprite()->getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition())))
        this->aimed = true;
    else
        this->aimed = false;
        
}

Target::Target(sf::Vector2f direction, sf::Vector2f pos, std::string spritePath, double nSize, int oSize) : Entity(pos, spritePath, nSize, oSize)
{
    this->getSprite()->setOrigin(oSize/2, oSize/2);

    srand(time(NULL));
    this->direction = direction;
    this->speed = rand()%3 + 1;
    this->points = 10 * speed;
    this->speed *= 0.01;

    this->shooted = false;
}

Target::~Target() {}