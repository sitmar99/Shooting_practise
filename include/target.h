#ifndef TARGET_H
#define TARGET_H

#include "entity.h"
#include <iostream>

class Target: public Entity
{
private:
    int points;
    bool aimed;
    sf::Vector2f direction;
    float speed;

    bool shooted;

public:
    int getPoints() { return this->points; }
    bool getAimed() { return this->aimed; }
    bool getShooted() { return this->shooted; }
    bool setShooted(bool nShooted) { return shooted = nShooted; }

    void update();

    Target(sf::Vector2f direction, sf::Vector2f pos, std::string spritePath, double nSize, int oSize);
    ~Target();
};

#endif