#ifndef CROSSHAIR_H
#define CROSSHAIR_H

#include "entity.h"

class Crosshair: public Entity
{
private:

public:

	void update();

	Crosshair(std::string spritePath, double nSize, int oSize);
	~Crosshair();
	
};

#endif