#ifndef CROSSHAIR_H
#define CROSSHAIR_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>

class crosshair: public sf::Sprite
{
private:
	//Tekstury
	sf::IntRect rect;
	sf::Texture texture;
	sf::Sprite sprite;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:

	void update();

	void setRect(sf::IntRect nRect) { rect = nRect; };
	sf::Texture* getTexture() { return &this->texture; };
	sf::Sprite* getSprite() { return &this->sprite; };

	crosshair();
	~crosshair();
	
};

#endif