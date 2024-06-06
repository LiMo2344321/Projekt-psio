#ifndef HERO_H
#define HERO_H

#include "Postac.h"
#include <algorithm>

class Hero : public Postac {
public:
    Hero(const sf::Texture& texture, float gravity, float moveSpeed, float jumpSpeed)
        : Postac(gravity), moveSpeed(moveSpeed), jumpSpeed(jumpSpeed) {
        sprite.setTexture(texture);
    }

    void handleInput(const std::vector<sf::RectangleShape>& platforms, float groundHeight) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            velocity.x = moveSpeed;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            velocity.x = -moveSpeed;
        else
            velocity.x = 0;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
            (sprite.getPosition().y + sprite.getGlobalBounds().height >= groundHeight ||
                std::any_of(platforms.begin(), platforms.end(), [this](const sf::RectangleShape& platform) {
                    return (sprite.getPosition().y + sprite.getGlobalBounds().height <= platform.getPosition().y + 10 &&
                        sprite.getPosition().x + sprite.getGlobalBounds().width > platform.getPosition().x &&
                        sprite.getPosition().x < platform.getPosition().x + platform.getSize().x);
                    }))
            ) {
            velocity.y = -jumpSpeed;
        }
    }

private:
    float moveSpeed;
    float jumpSpeed;
};

#endif // HERO_H
