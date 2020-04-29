#include "target.h"

void Target::update()
{
    if (this->getSprite()->getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition())))
        this->aimed = true;
    else
        this->aimed = false;
        
}

Target::Target(sf::Vector2f pos, std::string spritePath, double nSize, int oSize) : Entity(pos, spritePath, nSize, oSize)
{
    this->getSprite()->setOrigin(oSize/2, oSize/2);
    this->points = 10;
}

Target::~Target() {}