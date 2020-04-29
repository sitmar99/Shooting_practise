#ifndef TARGET_H
#define TARGET_H

#include "entity.h"
#include <iostream>

class Target: public Entity
{
private:
    int points;
    bool aimed;

public:
    int getPoints() { return this->points; }
    bool getAimed() { return this->aimed; }

    void update();

    Target(sf::Vector2f pos, std::string spritePath, double nSize, int oSize);
    ~Target();
};

#endif