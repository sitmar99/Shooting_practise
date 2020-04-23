#include "crosshair.h"

void Crosshair::update()
{
	this->getSprite()->setPosition(sf::Vector2f(sf::Mouse::getPosition()));
}

Crosshair::Crosshair(std::string spritePath, double nSize, int oSize) : Entity(spritePath, nSize, oSize)
{
	this->getSprite()->setOrigin(256,256);
}

Crosshair::~Crosshair() {}