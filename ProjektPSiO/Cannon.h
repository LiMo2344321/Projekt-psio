#ifndef CANNON_H
#define CANNON_H

#include "Enemy.h"

class Cannon : public Enemy {
public:
    Cannon(float gravity)
        : Enemy(gravity) {
        if (!texture.loadFromFile("cannonidle.png")) {
            std::cerr << "Error loading cannon texture" << std::endl;
        }
        sprite.setTexture(texture);
        sprite.setScale(3.0f, 3.0f);
    }

    void update(float groundHeight) override {
        // Add cannon-specific update logic here if needed
        Enemy::update(groundHeight);
    }

private:
    sf::Texture texture;
};

#endif // CANNON_H
