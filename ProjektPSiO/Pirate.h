#ifndef PIRATE_H
#define PIRATE_H

#include "Enemy.h"
#include <vector>
#include <SFML/Graphics.hpp>

class Pirate : public Enemy {
public:
    enum State { Idle, Running, Attacking, Hit, Dead };

    Pirate(const std::vector<sf::Texture>& idleTextures, const std::vector<sf::Texture>& runTextures,
        const std::vector<sf::Texture>& attackTextures, const sf::Texture& hitTexture, const sf::Texture& dieTexture,
        float gravity, float speed)
        : Enemy(gravity, 3), idleTextures(idleTextures), runTextures(runTextures), attackTextures(attackTextures),
        hitTexture(hitTexture), dieTexture(dieTexture), speed(speed), movingRight(true), state(Idle), currentFrame(0),
        frameTime(sf::seconds(0.1f)), runTime(sf::seconds(0.4f)), attackTime(sf::seconds(1.0f)),
        hitDuration(sf::seconds(0.5f)), hitElapsedTime(sf::Time::Zero), deathDisplayTime(sf::seconds(1.0f)),
        deathElapsedTime(sf::Time::Zero) {
        sprite.setTexture(idleTextures[0]);
        sprite.setScale(1.8f, 1.8f);
        sprite.setOrigin(sprite.getGlobalBounds().width / 2, 0);
        stateClock.restart();
        animationClock.restart();
    }

    void update(const sf::RectangleShape& platform, const sf::Sprite& heroSprite, sf::Time deltaTime) {
        if (state == Dead) {
            deathElapsedTime += deltaTime;
            if (deathElapsedTime < deathDisplayTime) {
                sprite.setTexture(dieTexture);
            }
            return;
        }

        if (state == Hit) {
            hitElapsedTime += deltaTime;
            if (hitElapsedTime >= hitDuration) {
                state = Idle;
                hitElapsedTime = sf::Time::Zero;
            }
            else {
                sprite.setTexture(hitTexture);
                return;
            }
        }

        sf::Vector2f heroPosition = heroSprite.getPosition();
        sf::Vector2f piratePosition = sprite.getPosition();

        switch (state) {
        case Idle:
            animate(idleTextures);
            if (abs(heroPosition.x - piratePosition.x) < 300) {
                state = Running;
                stateClock.restart();
            }
            break;

        case Running:
            animate(runTextures);
            if (stateClock.getElapsedTime() < runTime) {
                if (movingRight) {
                    sprite.move(speed, 0);
                    sprite.setScale(1.8f, 1.8f);
                    if (sprite.getPosition().x + sprite.getGlobalBounds().width / 2 > platform.getPosition().x + platform.getSize().x) {
                        movingRight = false;
                    }
                }
                else {
                    sprite.move(-speed, 0);
                    sprite.setScale(-1.8f, 1.8f);
                    if (sprite.getPosition().x - sprite.getGlobalBounds().width / 2 < platform.getPosition().x) {
                        movingRight = true;
                    }
                }
            }
            else {
                state = Attacking;
                stateClock.restart();
            }
            break;

        case Attacking:
            animate(attackTextures);
            if (stateClock.getElapsedTime() >= attackTime) {
                state = Idle;
                stateClock.restart();
            }
            break;
        }
    }

    bool getIsAttacking() const {
        return state == Attacking;
    }

    void takeDamage(int damage) {
        health -= damage;
        if (health <= 0) {
            state = Dead;
            deathElapsedTime = sf::Time::Zero;
        }
        else {
            state = Hit;
            hitElapsedTime = sf::Time::Zero;
        }
    }

    bool isAlive() const {
        return state != Dead;
    }

    sf::Time getDeathElapsedTime() {
        return deathElapsedTime;
    }

    void reset() {
        movingRight = true;
        state = Idle;
        currentFrame = 0;
        stateClock.restart();
        animationClock.restart();
        sprite.setTexture(idleTextures[0]);
        sprite.setScale(1.8f, 1.8f);
        sprite.setOrigin(sprite.getGlobalBounds().width / 2, 0);
        health = 3; 
        hitElapsedTime = sf::Time::Zero;
        deathElapsedTime = sf::Time::Zero;
    }

private:
    std::vector<sf::Texture> idleTextures;
    std::vector<sf::Texture> runTextures;
    std::vector<sf::Texture> attackTextures;
    sf::Texture hitTexture;
    sf::Texture dieTexture;
    float speed;
    bool movingRight;
    State state;
    int currentFrame;
    sf::Clock stateClock;
    sf::Clock animationClock;
    sf::Time frameTime;
    sf::Time runTime;
    sf::Time attackTime;
    sf::Time hitDuration;
    sf::Time hitElapsedTime;
    sf::Time deathDisplayTime;
    sf::Time deathElapsedTime;

    void animate(const std::vector<sf::Texture>& textures) {
        if (animationClock.getElapsedTime() >= frameTime) {
            currentFrame = (currentFrame + 1) % textures.size();
            sprite.setTexture(textures[currentFrame]);
            animationClock.restart();
        }
    }
};

#endif