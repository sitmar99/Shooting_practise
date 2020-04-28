#ifndef TARGET_H
#define TARGET_H

#include "entity.h"

class Target: public Entity
{
private:
    int points;
    bool aimed;

public:
    bool getAimed() { return aimed; }

    void update();

    Target(sf::Vector2f pos, std::string spritePath, double nSize, int oSize);
    ~Target();
};

#endif