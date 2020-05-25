#ifndef MENUOPTION_H
#define MENUOPTION_H

#include "entity.h"

class menuOption : public Entity
{
private:
    bool aimed;
public:
    bool getAimed() { return this->aimed; }

    void update();

    menuOption(sf::Vector2f pos, std::string spritePath, sf::Vector2f nSize, sf::Vector2f oSize);
    ~menuOption();
};

#endif