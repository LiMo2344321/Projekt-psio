#ifndef CRAB_H
#define CRAB_H

#include "Enemy.h"
#include <SFML/Graphics.hpp>
#include <vector>

class Crab : public Enemy {
public:
    Crab(const std::vector<sf::Texture>& runTextures, const std::vector<sf::Texture>& attackTextures, float gravity, float speed)
        : Enemy(gravity), runTextures(runTextures), attackTextures(attackTextures), speed(speed), movingRight(true), animationTime(sf::seconds(0.2f)), currentFrame(0), elapsedTime(sf::Time::Zero), isAttacking(false), attackDuration(sf::seconds(1.0f)), attackElapsedTime(sf::Time::Zero) {
        sprite.setTexture(runTextures[0]);
        sprite.setScale(3.0f, 3.0f);
    }

    void update(const sf::RectangleShape& platform, const sf::Sprite& hero, sf::Time deltaTime) {
        float heroPositionX = hero.getPosition().x;
        float crabPositionX = sprite.getPosition().x;
        float platformStartX = platform.getPosition().x;
        float platformEndX = platform.getPosition().x + platform.getSize().x;

        if (isAttacking) {
            attackElapsedTime += deltaTime;
            if (attackElapsedTime >= attackDuration) {
                isAttacking = false;
                attackElapsedTime = sf::Time::Zero;
                currentFrame = 0;
            }
        }
        else if (std::abs(heroPositionX - crabPositionX) < 20.0f)
        {
            isAttacking = true;
            currentFrame = 0;
        }
        else if (crabPositionX < platformStartX) {
            movingRight = true;
            sprite.move(speed, 0);
        }
        else if (crabPositionX > platformEndX) {
            movingRight = false;
            sprite.move(-speed, 0);
        }
        else if (movingRight) {
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
            if (isAttacking) {
                if (currentFrame >= attackTextures.size()) {
                    currentFrame = 0;
                }
                sprite.setTexture(attackTextures[currentFrame]);
            }
            else {
                if (currentFrame >= runTextures.size()) {
                    currentFrame = 0;
                }
                sprite.setTexture(runTextures[currentFrame]);
            }
            if (movingRight) {
                sprite.setScale(3.0f, 3.0f);
            }
            else {
                sprite.setScale(-3.0f, 3.0f);
            }
        }
    }

    void setPosition(float x, float y) {
        sprite.setPosition(x, y);
    }

    sf::Sprite& getSprite() {
        return sprite;
    }

    bool getisAttacking() {
        return isAttacking;
    }

private:
    sf::Sprite sprite;
    std::vector<sf::Texture> runTextures;
    std::vector<sf::Texture> attackTextures;
    float speed;
    bool movingRight;
    unsigned int currentFrame;
    sf::Time animationTime;
    sf::Time elapsedTime;
    bool isAttacking;
    sf::Time attackDuration;
    sf::Time attackElapsedTime;
};

#endif
