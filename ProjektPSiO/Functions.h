#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Hero.h"
#include "Cannon.h"
#include "Crab.h"
#include "BigGuy.h"
#include "Pirate.h"
#include "Captain.h"
#include "Collectable.h"
#include "Chest.h"

void loadMap(int mapIndex, std::vector<sf::RectangleShape>& platforms, std::vector<sf::Sprite>& backgroundElements, std::vector<sf::Sprite>& spikes, int groundHeight, sf::Texture& spikeTexture, std::vector <sf::Texture>& level1textures, std::vector <sf::Texture>& level2textures, std::vector <sf::Texture>& level3textures);

void handleCollisions(Postac& character, const std::vector<sf::RectangleShape>& platforms);

void resetGame(Hero& hero, Crab& crab, BigGuy& guy1, BigGuy& guy2, Pirate& pirate, Captain& captain, Collectable& key, Collectable& heart1, Collectable& heart2, std::vector<sf::RectangleShape>& platforms, std::vector<sf::Sprite>& spikes, std::vector<sf::Sprite>& backgroundElements, int& currentMap, int groundHeight, sf::Texture& spikeTexture, std::vector <sf::Texture>& level1textures, std::vector <sf::Texture>& level2textures, std::vector <sf::Texture>& level3textures, Chest& chest);

bool isHeroInFront(const sf::Sprite& enemy, const sf::Sprite& hero);

#endif 

