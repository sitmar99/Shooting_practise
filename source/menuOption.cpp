#include "menuOption.h"

void menuOption::update()
{
    if (this->getSprite()->getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition())))
        this->aimed = true;
    else
        this->aimed = false;
}

menuOption::menuOption(sf::Vector2f pos, std::string spritePath, sf::Vector2f nSize, sf::Vector2f oSize): Entity(pos, spritePath, nSize, oSize)
{

}

menuOption::~menuOption() {}