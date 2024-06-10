#ifndef CAPTAIN_H
#define CAPTAIN_H

#include "Enemy.h"
#include <SFML/Graphics.hpp>
#include <vector>

class Captain : public Enemy {
public:
    Captain(const std::vector<sf::Texture>& walkTextures, const std::vector<sf::Texture>& attackTextures, float gravity, float speed)
        : Enemy(gravity), walkTextures(walkTextures), attackTextures(attackTextures), speed(speed), movingRight(true),
        detectionRange(250.0f), attackRange(20.0f), currentFrame(0), animationTime(sf::seconds(0.1f)), elapsedTime(sf::Time::Zero),
        isAttacking(false), attackDuration(sf::seconds(1.0f)), attackElapsedTime(sf::Time::Zero), attackCooldown(sf::seconds(2.0f)),
        cooldownElapsedTime(sf::Time::Zero) {
        sprite.setTexture(walkTextures[0]);
        sprite.setScale(1.8f, 1.8f);
    }

    void update(const sf::RectangleShape& platform, const sf::Sprite& heroSprite, sf::Time deltaTime) {
        float heroPositionX = heroSprite.getPosition().x;
        float captainPositionX = sprite.getPosition().x;
        float platformStartX = platform.getPosition().x;
        float platformEndX = platform.getPosition().x + platform.getSize().x;

        bool moving = true;

        cooldownElapsedTime += deltaTime;

        if (isAttacking) {
            attackElapsedTime += deltaTime;
            if (attackElapsedTime >= attackDuration) {
                isAttacking = false;
                attackElapsedTime = sf::Time::Zero;
                currentFrame = 0;
            }
        }
        else if (cooldownElapsedTime >= attackCooldown && std::abs(heroPositionX - captainPositionX) < detectionRange) {
            if (std::abs(heroPositionX - captainPositionX) < attackRange) {
                isAttacking = true;
                currentFrame = 0;
                cooldownElapsedTime = sf::Time::Zero;
            }
        }

        if (!isAttacking) {
            if (movingRight) {
                sprite.move(speed, 0);
                if (sprite.getPosition().x + sprite.getGlobalBounds().width > platformEndX) {
                    movingRight = false;
                }
            }
            else {
                sprite.move(-speed, 0);
                if (sprite.getPosition().x < platformStartX) {
                    movingRight = true;
                }
            }
        }

        sf::FloatRect bounds = sprite.getLocalBounds();
        sprite.setOrigin(bounds.width / 2, 0);

        elapsedTime += deltaTime;
        if (elapsedTime >= animationTime) {
            elapsedTime -= animationTime;
            currentFrame++;
            if (isAttacking) {
                if (currentFrame >= attackTextures.size()) {
                    currentFrame = 0;
                }
                sprite.setTexture(attackTextures[currentFrame]);
            }
            else {
                if (currentFrame >= walkTextures.size()) {
                    currentFrame = 0;
                }
                sprite.setTexture(walkTextures[currentFrame]);
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

    bool getisAttacking() const {
        return isAttacking;
    }

private:
    sf::Sprite sprite;
    std::vector<sf::Texture> walkTextures;
    std::vector<sf::Texture> attackTextures;
    float speed;
    bool movingRight;
    float detectionRange;
    float attackRange;
    unsigned int currentFrame;
    sf::Time animationTime;
    sf::Time elapsedTime;
    bool isAttacking;
    sf::Time attackDuration;
    sf::Time attackElapsedTime;
    sf::Time attackCooldown;
    sf::Time cooldownElapsedTime;
};

#endif 