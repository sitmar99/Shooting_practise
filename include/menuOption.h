#ifndef MENUOPTION_H
#define MENUOPTION_H

#include "entity.h"

class menuOption : public Entity
{
private:
    bool aimed;
    int id;
public:
    bool getAimed() { return this->aimed; }
    int getID() { return this->id; }

    void update();

    menuOption(sf::Vector2f pos, std::string spritePath, int id, sf::Vector2f nSize, sf::Vector2f oSize);
    ~menuOption();
};

#endif