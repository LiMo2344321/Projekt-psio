#ifndef CRAB_H
#define CRAB_H

#include "Enemy.h"
#include <SFML/Graphics.hpp>
#include <vector>

class Crab : public Enemy {
public:
    Crab(const std::vector<sf::Texture>& runTextures, const std::vector<sf::Texture>& attackTextures, const std::vector<sf::Texture>& anticipationTextures, const std::vector<sf::Texture>& hitTextures, const std::vector<sf::Texture>& dieTextures, float gravity, float speed)
        : Enemy(gravity, 1), runTextures(runTextures), attackTextures(attackTextures), anticipationTextures(anticipationTextures), hitTextures(hitTextures), dieTextures(dieTextures), speed(speed), movingRight(true), frameDuration(sf::seconds(0.5f)), currentFrame(0), elapsedTime(sf::Time::Zero), isAttacking(false), attackDuration(sf::seconds(1.0f)), attackElapsedTime(sf::Time::Zero), isAnticipating(false), anticipationDuration(sf::seconds(0.5f)), anticipationElapsedTime(sf::Time::Zero), isHit(false), hitDuration(sf::seconds(0.5f)), hitElapsedTime(sf::Time::Zero), isDying(false), dieElapsedTime(sf::Time::Zero), isAlive(true) {
        sprite.setTexture(runTextures[0]);
        sprite.setScale(3.0f, 3.0f);
    }

    void update(const sf::RectangleShape& platform, const sf::Sprite& hero, sf::Time deltaTime) {
        if (!isAlive) return;

        if (isDying) {
            dieElapsedTime += deltaTime;
            if (dieElapsedTime >= sf::seconds(dieTextures.size() * frameDuration.asSeconds())) {
                isAlive = false;
                return;
            }
            updateAnimation(dieTextures, dieElapsedTime);
            return;
        }

        if (isHit) {
            hitElapsedTime += deltaTime;
            if (hitElapsedTime >= hitDuration) {
                isHit = false;
                hitElapsedTime = sf::Time::Zero;
                currentFrame = 0;
            }
            updateAnimation(hitTextures, hitElapsedTime);
            return;
        }

        if (isAnticipating) {
            anticipationElapsedTime += deltaTime;
            if (anticipationElapsedTime >= anticipationDuration) {
                isAnticipating = false;
                isAttacking = true;
                anticipationElapsedTime = sf::Time::Zero;
                currentFrame = 0;
            }
            updateAnimation(anticipationTextures, anticipationElapsedTime);
            return;
        }

        if (isAttacking) {
            attackElapsedTime += deltaTime;
            if (attackElapsedTime >= attackDuration) {
                isAttacking = false;
                attackElapsedTime = sf::Time::Zero;
                currentFrame = 0;
            }
            updateAnimation(attackTextures, attackElapsedTime);
        }
        else {
            float heroPositionX = hero.getPosition().x;
            float crabPositionX = sprite.getPosition().x;
            float platformStartX = platform.getPosition().x;
            float platformEndX = platform.getPosition().x + platform.getSize().x;

            if (std::abs(heroPositionX - crabPositionX) < 20.0f && !isAttacking && !isHit) {
                isAnticipating = true;
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

            updateAnimation(runTextures, elapsedTime);
        }

        sf::FloatRect bounds = sprite.getLocalBounds();
        sprite.setOrigin(bounds.width / 2, 0);

        if (movingRight) {
            sprite.setScale(3.0f, 3.0f);
        }
        else {
            sprite.setScale(-3.0f, 3.0f);
        }
    }

    void takeDamage(int damage) {
        if (isDying) return;

        Enemy::takeDamage(damage);
        if (!Enemy::isAlive()) {
            isDying = true;
            dieElapsedTime = sf::Time::Zero;
            currentFrame = 0;
        }
        else {
            isHit = true;
            hitElapsedTime = sf::Time::Zero;
            currentFrame = 0;
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

    bool isCrabAlive() const {
        return isAlive;
    }

private:
    sf::Sprite sprite;
    std::vector<sf::Texture> runTextures;
    std::vector<sf::Texture> attackTextures;
    std::vector<sf::Texture> anticipationTextures;
    std::vector<sf::Texture> hitTextures;
    std::vector<sf::Texture> dieTextures;
    float speed;
    bool movingRight;
    unsigned int currentFrame;
    sf::Time frameDuration;
    sf::Time elapsedTime;
    bool isAttacking;
    sf::Time attackDuration;
    sf::Time attackElapsedTime;
    bool isAnticipating;
    sf::Time anticipationDuration;
    sf::Time anticipationElapsedTime;
    bool isHit;
    sf::Time hitDuration;
    sf::Time hitElapsedTime;
    bool isDying;
    sf::Time dieElapsedTime;
    bool isAlive;

    void updateAnimation(const std::vector<sf::Texture>& textures, sf::Time& elapsedTime) {
        elapsedTime += frameDuration;
        if (elapsedTime >= frameDuration) {
            elapsedTime -= frameDuration;
            currentFrame++;
            if (currentFrame >= textures.size()) {
                currentFrame = 0;
            }
            sprite.setTexture(textures[currentFrame]);
        }
    }
};

#endif
