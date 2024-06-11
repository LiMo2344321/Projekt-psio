#ifndef CANNON_H
#define CANNON_H

#include "Enemy.h"
#include <vector>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

class Cannonball {
public:
    Cannonball(const sf::Texture& texture, float speed, const sf::Vector2f& position)
        : speed(speed) {
        sprite.setTexture(texture);
        sprite.setScale(3.0f, 3.0f);
        sprite.setPosition(position);
    }

    void update() {
        sprite.move(speed, 0); 
    }

    const sf::Sprite& getSprite() const {
        return sprite;
    }

    sf::FloatRect getGlobalBounds() const {
        return sprite.getGlobalBounds();
    }

    bool operator==(const Cannonball& other) const {
        return sprite.getPosition() == other.sprite.getPosition() && speed == other.speed;
    }

private:
    sf::Sprite sprite;
    float speed;
};

class Cannon : public Enemy {
public:
    Cannon(float gravity, const sf::Texture& cannonballTexture)
        : Enemy(gravity, 10), cannonballTexture(cannonballTexture), currentMap(1), currentTextureIndex(0), stepsSinceLastSpriteChange(0), shooting(false) {
        if (!texture.loadFromFile("Cannon/cannonidle.png")) {
            std::cerr << "Error loading cannon texture" << std::endl;
        }
        sprite.setTexture(texture);
        sprite.setScale(3.0f, 3.0f);
    }

    void addShootTexture(const sf::Texture& texture) {
        shootTextures.push_back(texture);
    }

    void update(float groundHeight) override {        
        if (currentMap == 1) {
            shoot();
        }
        updateCannonballs();
        updateAnimation();
    }

    void shoot() {
        if (shootClock.getElapsedTime().asSeconds() >= 2.0f) {
            cannonballs.emplace_back(cannonballTexture, -0.2f, sprite.getPosition());
            shootClock.restart();
            currentTextureIndex = 0; 
            stepsSinceLastSpriteChange = 0;
            shooting = true; 
        }
    }

    void updateCannonballs() {
        for (auto& cannonball : cannonballs) {
            cannonball.update();
        }
        cannonballs.erase(std::remove_if(cannonballs.begin(), cannonballs.end(), [&](const Cannonball& cb) {
            return cb.getSprite().getPosition().x < 0; 
            }), cannonballs.end());
    }

    std::vector<Cannonball>& getCannonballs() {
        return cannonballs;
    }

    void setMap(int map) {
        currentMap = map;
    }

private:
    sf::Texture texture;
    sf::Texture cannonballTexture;
    std::vector<sf::Texture> shootTextures;
    std::vector<Cannonball> cannonballs;
    sf::Clock shootClock;
    int currentMap;
    size_t currentTextureIndex;
    int stepsSinceLastSpriteChange;
    bool shooting;

    void updateAnimation() {
        const int stepsBetweenSprites = 70; 

        if (shooting && !shootTextures.empty() && stepsSinceLastSpriteChange >= stepsBetweenSprites) {
            currentTextureIndex++;
            if (currentTextureIndex >= shootTextures.size()) {
                currentTextureIndex = 0;
                shooting = false; 
                sprite.setTexture(texture); 
            }
            else {
                sprite.setTexture(shootTextures[currentTextureIndex]);
            }
            adjustOriginAndScale();
            stepsSinceLastSpriteChange = 0;
        }
        else {
            stepsSinceLastSpriteChange++;
        }
    }

    void adjustOriginAndScale() {
        sf::Vector2f currentPosition = sprite.getPosition(); 
        sprite.setPosition(currentPosition); 
    }
};


#endif 
