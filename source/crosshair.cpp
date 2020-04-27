#include "crosshair.h"

void Crosshair::update()
{
	this->getSprite()->setPosition(sf::Vector2f(sf::Mouse::getPosition()));
}

Crosshair::Crosshair(std::string spritePath, double nSize, int oSize) : Entity(spritePath, nSize, oSize)
{
	sf::Sprite *s = this->getSprite();
	s->setPosition(sf::Vector2f(sf::Mouse::getPosition()));
	s->setOrigin(256,256);
}

Crosshair::~Crosshair() {}