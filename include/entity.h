#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <string>

class Entity: public sf::Sprite
{
private:
	//Tekstury
	sf::IntRect rect;
	sf::Texture texture;
	sf::Sprite sprite;

    //Draw
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
    //Tekstury
	sf::Texture* getTexture() { return &this->texture; };
	sf::Sprite* getSprite() { return &this->sprite; };

    //Update
    virtual void update() = 0;

    //Konstruktory i destruktory
    Entity(std::string spritePath, double nSize, int oSize);
    Entity(sf::Vector2f pos, std::string spritePath, double nSize, int oSize);
    Entity(sf::Vector2f pos, std::string spritePath, sf::Vector2f nSize, sf::Vector2f oSize);
    ~Entity();
};

#endif