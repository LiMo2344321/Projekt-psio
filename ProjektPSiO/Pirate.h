#ifndef PIRATE_H
#define PIRATE_H

#include "Enemy.h"
#include <vector>
#include <SFML/Graphics.hpp>

class Pirate : public Enemy {
public:
    enum State { Idle, Running, Attacking };

    Pirate(const std::vector<sf::Texture>& idleTextures, const std::vector<sf::Texture>& runTextures, const std::vector<sf::Texture>& attackTextures, float gravity, float speed)
        : Enemy(gravity, 3), idleTextures(idleTextures), runTextures(runTextures), attackTextures(attackTextures), speed(speed), movingRight(true), state(Idle), currentFrame(0), frameTime(sf::seconds(0.1f)), runTime(sf::seconds(0.4f)), attackTime(sf::seconds(1.0f)) {
        sprite.setTexture(idleTextures[0]);
        sprite.setScale(1.8f, 1.8f);
        sprite.setOrigin(sprite.getGlobalBounds().width / 2, 0); 
        stateClock.restart();
        animationClock.restart();
    }

    void update(const sf::RectangleShape& platform, const sf::Sprite& heroSprite) {
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


    bool getisAttacking() {
        return state == State::Attacking;
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
    }

private:
    std::vector<sf::Texture> idleTextures;
    std::vector<sf::Texture> runTextures;
    std::vector<sf::Texture> attackTextures;
    float speed;
    bool movingRight;
    State state;
    int currentFrame;
    sf::Clock stateClock;
    sf::Clock animationClock;
    sf::Time frameTime;
    sf::Time runTime;
    sf::Time attackTime;

    void animate(const std::vector<sf::Texture>& textures) {
        if (animationClock.getElapsedTime() >= frameTime) {
            currentFrame = (currentFrame + 1) % textures.size();
            sprite.setTexture(textures[currentFrame]);
            animationClock.restart();
        }
    }
};

#endif 