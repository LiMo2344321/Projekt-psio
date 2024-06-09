#ifndef BIGGUY_H
#define BIGGUY_H

#include "Enemy.h"
#include <SFML/Graphics.hpp>
#include <vector>

class BigGuy : public Enemy {
public:
    BigGuy(const std::vector<sf::Texture>& idleTextures, const std::vector<sf::Texture>& runTextures, const std::vector<sf::Texture>& attackTextures, float gravity, float speed)
        : Enemy(gravity), idleTextures(idleTextures), runTextures(runTextures), attackTextures(attackTextures), speed(speed), movingRight(true), detectionRange(200.0f), attackRange(50.0f), currentFrame(0), animationTime(sf::seconds(0.1f)), elapsedTime(sf::Time::Zero), isAttacking(false), attackDuration(sf::seconds(1.0f)), attackElapsedTime(sf::Time::Zero) {
        sprite.setTexture(idleTextures[0]);
        sprite.setScale(2.0f, 2.0f);
    }

    void update(const sf::RectangleShape& platform, const sf::Sprite& heroSprite, sf::Time deltaTime) {
        float heroPositionX = heroSprite.getPosition().x;
        float bigGuyPositionX = sprite.getPosition().x;
        float platformStartX = platform.getPosition().x;
        float platformEndX = platform.getPosition().x + platform.getSize().x;

        bool moving = false;

        // SprawdŸ, czy BigGuy jest w trakcie ataku
        if (isAttacking) {
            attackElapsedTime += deltaTime;
            if (attackElapsedTime >= attackDuration) {
                isAttacking = false;
                attackElapsedTime = sf::Time::Zero;
                currentFrame = 0;
            }
        }
        else {
            // SprawdŸ, czy postaæ gracza znajduje siê w zasiêgu wykrywania
            if (std::abs(heroPositionX - bigGuyPositionX) < detectionRange) {
                // SprawdŸ, czy gracz jest w zasiêgu ataku
                if (std::abs(heroPositionX - bigGuyPositionX) < attackRange) {
                    isAttacking = true;
                    currentFrame = 0;
                }
                else {
                    // Poruszaj siê w kierunku postaci gracza
                    if (heroPositionX > bigGuyPositionX && (bigGuyPositionX + sprite.getGlobalBounds().width) < platformEndX) {
                        sprite.move(speed, 0);
                        moving = true;
                        movingRight = true;
                    }
                    else if (heroPositionX < bigGuyPositionX && bigGuyPositionX > platformStartX) {
                        sprite.move(-speed, 0);
                        moving = true;
                        movingRight = false;
                    }
                }
            }
        }

        // Upewnij siê, ¿e BigGuy nie spada z platformy
        if (sprite.getPosition().x < platformStartX) {
            sprite.setPosition(platformStartX, sprite.getPosition().y);
        }
        if (sprite.getPosition().x + sprite.getGlobalBounds().width > platformEndX) {
            sprite.setPosition(platformEndX - sprite.getGlobalBounds().width, sprite.getPosition().y);
        }

        sf::FloatRect bounds = sprite.getLocalBounds();
        sprite.setOrigin(bounds.width / 2, 0);

        // Aktualizacja animacji
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
            else if (moving) {
                if (currentFrame >= runTextures.size()) {
                    currentFrame = 0;
                }
                sprite.setTexture(runTextures[currentFrame]);
            }
            else {
                if (currentFrame >= idleTextures.size()) {
                    currentFrame = 0;
                }
                sprite.setTexture(idleTextures[currentFrame]);
            }
            if (movingRight) {
                sprite.setScale(2.0f, 2.0f);
            }
            else {
                sprite.setScale(-2.0f, 2.0f);
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
    std::vector<sf::Texture> idleTextures;
    std::vector<sf::Texture> runTextures;
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
};

#endif