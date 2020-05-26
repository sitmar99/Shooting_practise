#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

#include <vector>
#include <deque>
#include <memory>
#include <time.h>
#include <thread>
#include <pthread.h>
#include <iostream>
#include <fstream>

#include "functions.h"
#include "entity.h"
#include "crosshair.h"
#include "target.h"
#include "menuOption.h"

void addTarget(std::deque<std::shared_ptr<Entity>> &entities, int width, int height);
void drawHiScore(sf::RenderWindow &window, sf::Text text, int height, int width);
void drawMenu(sf::RenderWindow &window, std::deque<std::shared_ptr<Entity>> &menuEntities);
void drawPoints(sf::RenderWindow &window, sf::Text text, int height, int width, int points, std::deque<std::shared_ptr<Entity>> &entities);
int Game(sf::Event event, std::deque<std::shared_ptr<Entity>> &entities, int &points, sf::Sound &gunShoot);
int HiScore(sf::Event event);
int Menu(sf::Event event, std::deque<std::shared_ptr<Entity>> &menuEntities, sf::Sound &gunShoot);
void update(std::deque<std::shared_ptr<Entity>> &entities, int width, int height, int &points);
void updateMenu(std::deque<std::shared_ptr<Entity>> &menuEntities);


#endif