#ifndef PIRATE_H
#define PIRATE_H

#include "Enemy.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream> // Dodajemy bibliotekê do debugowania

class Pirate : public Enemy {
public:
    Pirate(const std::vector<sf::Texture>& idleTextures, const std::vector<sf::Texture>& runTextures, const std::vector<sf::Texture>& attackTextures, float gravity, float speed)
        : Enemy(gravity), idleTextures(idleTextures), runTextures(runTextures), attackTextures(attackTextures), speed(speed), movingRight(true), detectionRange(250.0f), chargeRange(200.0f), currentFrame(0), animationTime(sf::seconds(0.1f)), elapsedTime(sf::Time::Zero), isCharging(false), isAttacking(false), chargeDuration(sf::seconds(0.5f)), actionElapsedTime(sf::Time::Zero) {
        sprite.setTexture(idleTextures[0]);
        sprite.setScale(1.8f, 1.8f);
    }

    void update(const sf::RectangleShape& platform, const sf::Sprite& heroSprite, sf::Time deltaTime) {
        float heroPositionX = heroSprite.getPosition().x;
        float piratePositionX = sprite.getPosition().x;
        float platformStartX = platform.getPosition().x;
        float platformEndX = platform.getPosition().x + platform.getSize().x;

        if (isCharging) {            
            actionElapsedTime += deltaTime;
            if (actionElapsedTime < chargeDuration) {
                float chargeSpeed = speed;
                if (movingRight) {
                    sprite.move(chargeSpeed * deltaTime.asSeconds(), 0);
                }
                else {
                    sprite.move(-chargeSpeed * deltaTime.asSeconds(), 0);
                }
            }
            else {
                isCharging = false;
                isAttacking = true;
                actionElapsedTime = sf::Time::Zero;
                currentFrame = 0;
            }
        }
        else if (isAttacking) {
            actionElapsedTime += deltaTime;
            if (actionElapsedTime >= chargeDuration) {
                isAttacking = false;
                actionElapsedTime = sf::Time::Zero;
                currentFrame = 0;
            }
        }
        else {
            if (std::abs(heroPositionX - piratePositionX) < detectionRange) {
                if (std::abs(heroPositionX - piratePositionX) < chargeRange) {
                    isCharging = true;
                    movingRight = heroPositionX > piratePositionX;
                    currentFrame = 0;
                }
            }
        }

        if (sprite.getPosition().x < platformStartX) {
            sprite.setPosition(platformStartX, sprite.getPosition().y);
        }
        if (sprite.getPosition().x + sprite.getGlobalBounds().width > platformEndX) {
            sprite.setPosition(platformEndX - sprite.getGlobalBounds().width, sprite.getPosition().y);
        }

        sf::FloatRect bounds = sprite.getLocalBounds();
        sprite.setOrigin(bounds.width / 2, 0);

        elapsedTime += deltaTime;
        if (elapsedTime >= animationTime) {
            elapsedTime -= animationTime;
            currentFrame++;
            if (isCharging) {
                if (currentFrame >= runTextures.size()) {
                    currentFrame = 0;
                }
                sprite.setTexture(runTextures[currentFrame]);
            }
            else if (isAttacking) {
                if (currentFrame >= attackTextures.size()) {
                    currentFrame = 0;
                }
                sprite.setTexture(attackTextures[currentFrame]);
            }
            else {
                if (currentFrame >= idleTextures.size()) {
                    currentFrame = 0;
                }
                sprite.setTexture(idleTextures[currentFrame]);
            }
            if (movingRight) {
                sprite.setScale(1.8f, 1.8f);
            }
            else {
                sprite.setScale(-1.8f, 1.8f);
            }
        }
    }

    void setPosition(float x, float y) {
        sprite.setPosition(x, y);
    }

    sf::Sprite& getSprite() {
        return sprite;
    }

    bool getisCharging() {
        return isCharging;
    }

    bool getisAttacking() {
        return isAttacking;
    }

private:
    sf::Sprite sprite;
    std::vector<sf::Texture> idleTextures;
    std::vector<sf::Texture> runTextures;
    std::vector<sf::Texture> attackTextures;
    float speed;
    bool movingRight;
    float detectionRange;
    float chargeRange;
    unsigned int currentFrame;
    sf::Time animationTime;
    sf::Time elapsedTime;
    bool isCharging;
    bool isAttacking;
    sf::Time chargeDuration;
    sf::Time actionElapsedTime;
};

#endif
