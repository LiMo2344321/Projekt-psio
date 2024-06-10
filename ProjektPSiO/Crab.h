#ifndef CRAB_H
#define CRAB_H

#include "Enemy.h"
#include <SFML/Graphics.hpp>
#include <vector>

class Crab : public Enemy {
public:
    Crab(const std::vector<sf::Texture>& walkTextures, const std::vector<sf::Texture>& anticipationTextures, const std::vector<sf::Texture>& attackTextures, const sf::Texture& hitTexture, const sf::Texture& dieTexture, float gravity, float speed)
        : Enemy(gravity, 2), walkTextures(walkTextures), anticipationTextures(anticipationTextures), attackTextures(attackTextures),
        hitTexture(hitTexture), dieTexture(dieTexture), speed(speed), movingRight(true),
        detectionRange(250.0f), attackRange(20.0f), currentFrame(0), animationTime(sf::seconds(0.1f)),
        elapsedTime(sf::Time::Zero), isAnticipating(false), anticipationDuration(sf::seconds(0.5f)),
        anticipationElapsedTime(sf::Time::Zero), isAttacking(false), attackDuration(sf::seconds(1.0f)),
        attackElapsedTime(sf::Time::Zero), attackCooldown(sf::seconds(2.0f)),
        cooldownElapsedTime(sf::Time::Zero), isHit(false), isDead(false), hitDuration(sf::seconds(0.5f)),
        hitElapsedTime(sf::Time::Zero), deathDisplayTime(sf::seconds(1.0f)), deathElapsedTime(sf::Time::Zero) {
        sprite.setTexture(walkTextures[0]);
        sprite.setScale(3.0f, 3.0f);
    }

    void update(const sf::RectangleShape& platform, const sf::Sprite& heroSprite, sf::Time deltaTime) {
        if (isDead) {
            deathElapsedTime += deltaTime;
            if (deathElapsedTime < deathDisplayTime) {
                sprite.setTexture(dieTexture);
            }
            return;
        }

        float heroPositionX = heroSprite.getPosition().x;
        float crabPositionX = sprite.getPosition().x;
        float platformStartX = platform.getPosition().x;
        float platformEndX = platform.getPosition().x + platform.getSize().x;

        cooldownElapsedTime += deltaTime;

        if (isHit) {
            hitElapsedTime += deltaTime;
            if (hitElapsedTime >= hitDuration) {
                isHit = false;
                hitElapsedTime = sf::Time::Zero;
                currentFrame = 0;
            }
            else {
                sprite.setTexture(hitTexture);
                return;
            }
        }

        if (isAnticipating) {
            anticipationElapsedTime += deltaTime;
            if (anticipationElapsedTime >= anticipationDuration) {
                isAnticipating = false;
                isAttacking = true;
                anticipationElapsedTime = sf::Time::Zero;
                currentFrame = 0;
            }
            else {
                sprite.setTexture(anticipationTextures[currentFrame]);
                return;
            }
        }

        if (isAttacking) {
            attackElapsedTime += deltaTime;
            if (attackElapsedTime >= attackDuration) {
                isAttacking = false;
                attackElapsedTime = sf::Time::Zero;
                currentFrame = 0;
            }
        }
        else if (cooldownElapsedTime >= attackCooldown && std::abs(heroPositionX - crabPositionX) < detectionRange) {
            if (std::abs(heroPositionX - crabPositionX) < attackRange) {
                isAnticipating = true;
                currentFrame = 0;
                cooldownElapsedTime = sf::Time::Zero;
            }
        }

        if (!isAnticipating && !isAttacking) {
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
            if (isAnticipating) {
                if (currentFrame >= anticipationTextures.size()) {
                    currentFrame = 0;
                }
                sprite.setTexture(anticipationTextures[currentFrame]);
            }
            else if (isAttacking) {
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

    bool getIsAttacking() const {
        return isAttacking;
    }

    bool getisAttacking() const {
        return isAttacking;
    }

    void takeDamage(int damage) {
        health -= damage;
        if (health <= 0) {
            isDead = true;
            sprite.setTexture(dieTexture);
            deathElapsedTime = sf::Time::Zero;
        }
        else {
            isHit = true;
            hitElapsedTime = sf::Time::Zero;
            sprite.setTexture(hitTexture);
        }
    }

    bool isAlive() const {
        return !isDead;
    }

    sf::Time getDeathElapsedTime() {
        return deathElapsedTime;
    }

private:
    sf::Sprite sprite;
    std::vector<sf::Texture> walkTextures;
    std::vector<sf::Texture> anticipationTextures;
    std::vector<sf::Texture> attackTextures;
    sf::Texture hitTexture;
    sf::Texture dieTexture;
    float speed;
    bool movingRight;
    float detectionRange;
    float attackRange;
    unsigned int currentFrame;
    sf::Time animationTime;
    sf::Time elapsedTime;
    bool isAnticipating;
    sf::Time anticipationDuration;
    sf::Time anticipationElapsedTime;
    bool isAttacking;
    sf::Time attackDuration;
    sf::Time attackElapsedTime;
    sf::Time attackCooldown;
    sf::Time cooldownElapsedTime;
    bool isHit;
    sf::Time hitDuration;
    sf::Time hitElapsedTime;
    bool isDead;
    sf::Time deathDisplayTime;
    sf::Time deathElapsedTime;
};

#endif