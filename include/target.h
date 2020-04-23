#ifndef TARGET_H
#define TARGET_H

#include "entity.h"

class Target: public Entity
{
private:

public:
    Target(std::string spritePath, double nSize, int oSize);
    ~Target();
};

#endif