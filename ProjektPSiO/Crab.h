#ifndef CRAB_H
#define CRAB_H

#include "Enemy.h"
#include <vector>

class Crab : public Enemy {
public:
    Crab(float gravity, float speed, float animationTime)
        : Enemy(gravity), speed(speed), movingRight(true), animationTime(animationTime), currentFrame(0) {
        sprite.setScale(3.0f, 3.0f);
    }

    void addRunTexture(const sf::Texture& texture) {
        runTextures.push_back(texture);
    }

    void update(const sf::RectangleShape& platform, sf::Time deltaTime) {
        animate(deltaTime);

        if (movingRight) {
            sprite.move(speed, 0);
            if (sprite.getPosition().x + sprite.getGlobalBounds().width > platform.getPosition().x + platform.getSize().x) {
                movingRight = false;
            }
        }
        else {
            sprite.move(-speed, 0);
            if (sprite.getPosition().x < platform.getPosition().x) {
                movingRight = true;
            }
        }
    }

private:
    float speed;
    bool movingRight;
    float animationTime;
    int currentFrame;
    std::vector<sf::Texture> runTextures;
    sf::Time elapsedTime;

    void animate(sf::Time deltaTime) {
        elapsedTime += deltaTime;

        if (elapsedTime.asSeconds() >= animationTime) {
            elapsedTime = sf::Time::Zero;
            currentFrame = (currentFrame + 1) % runTextures.size();
            sprite.setTexture(runTextures[currentFrame]);
        }
    }
};

#endif // CRAB_H