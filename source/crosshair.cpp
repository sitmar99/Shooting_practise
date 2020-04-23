#include "crosshair.h"

void Crosshair::update()
{
	this->getSprite()->setPosition(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
}

Crosshair::Crosshair(std::string spritePath, double nSize, int oSize) : Entity(spritePath, nSize, oSize)
{
	this->getSprite()->setOrigin(256,256);
}

Crosshair::~Crosshair() {}