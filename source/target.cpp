#include "target.h"

void Target::update()
{
    if (this->getSprite()->getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition())))
        aimed = true;
    else
        aimed = false;
        
}

Target::Target(sf::Vector2f pos, std::string spritePath, double nSize, int oSize) : Entity(pos, spritePath, nSize, oSize)
{
    this->getSprite()->setOrigin(oSize/2, oSize/2);
}

Target::~Target() {}