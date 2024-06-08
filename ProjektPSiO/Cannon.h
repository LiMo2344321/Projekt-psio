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
        sprite.move(speed, 0); // Move the cannonball horizontally
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
        : Enemy(gravity), cannonballTexture(cannonballTexture), currentMap(1) {
        if (!texture.loadFromFile("cannonidle.png")) {
            std::cerr << "Error loading cannon texture" << std::endl;
        }
        sprite.setTexture(texture);
        sprite.setScale(3.0f, 3.0f);
    }

    void update(float groundHeight) override {
        Enemy::update(groundHeight);
        if (currentMap == 1) {
            shoot();
        }
        updateCannonballs();
    }

    void shoot() {
        if (shootClock.getElapsedTime().asSeconds() >= 1.0f) {
            cannonballs.emplace_back(cannonballTexture, -0.2f, sprite.getPosition());
            shootClock.restart();
        }
    }

    void updateCannonballs() {
        for (auto& cannonball : cannonballs) {
            cannonball.update();
        }
        cannonballs.erase(std::remove_if(cannonballs.begin(), cannonballs.end(), [&](const Cannonball& cb) {
            return cb.getSprite().getPosition().x < 0; // Assuming the cannonballs should be removed when they go off the left side of the screen
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
    std::vector<Cannonball> cannonballs;
    sf::Clock shootClock;
    int currentMap;  // Dodaj tê zmienn¹
};

#endif // CANNON_H
