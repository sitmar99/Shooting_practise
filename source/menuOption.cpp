#include "menuOption.h"

void menuOption::update()
{
    if (this->getSprite()->getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition())))
        this->aimed = true;
    else
        this->aimed = false;
}

menuOption::menuOption(sf::Vector2f pos, std::string spritePath, int id): Entity(pos, spritePath)
{
    this->id = id;
}

menuOption::~menuOption() {}