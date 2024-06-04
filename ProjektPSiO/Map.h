#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <vector>

void loadMap(int mapIndex, std::vector<sf::RectangleShape>& platforms, std::vector<sf::Sprite>& backgroundElements, int groundHeight, sf::Texture& shipTexture, sf::Texture& mastTexture, sf::Texture& flagTexture);

#endif 
