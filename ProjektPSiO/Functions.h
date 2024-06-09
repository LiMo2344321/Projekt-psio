#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Hero.h"

void loadMap(int mapIndex, std::vector<sf::RectangleShape>& platforms, std::vector<sf::Sprite>& backgroundElements, std::vector<sf::Sprite>& spikes, int groundHeight, sf::Texture& shipTexture, sf::Texture& mastTexture, sf::Texture& flagTexture, sf::Texture& spikeTexture);

void handleCollisions(Postac& character, const std::vector<sf::RectangleShape>& platforms);
#endif 
