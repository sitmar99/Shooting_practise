#include "target.h"

void Target::update()
{
    if (this->getSprite()->getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition())))
        this->getSprite()->setRotation(90);
    else
        this->getSprite()->setRotation(0);
        
}

Target::Target(std::string spritePath, double nSize, int oSize) : Entity(spritePath, nSize, oSize)
{
    this->getSprite()->setOrigin(nSize/2, nSize/2);
}

Target::~Target() {}