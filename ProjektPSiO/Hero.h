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

        bool onGround = sprite.getPosition().y + sprite.getGlobalBounds().height >= groundHeight;

        bool onPlatform = false;
        for (const auto& platform : platforms) {
            sf::FloatRect heroBounds = sprite.getGlobalBounds();
            sf::FloatRect platformBounds = platform.getGlobalBounds();           
            platformBounds.top -= 1.0f; 
            platformBounds.height += 1.0f; 

            if (heroBounds.intersects(platformBounds)) {
                float heroBottom = heroBounds.top + heroBounds.height;
                float platformTop = platformBounds.top;

                if (heroBottom > platformTop && heroBottom < platformTop + 10) {
                    onPlatform = true;
                    sprite.setPosition(sprite.getPosition().x, platformTop - heroBounds.height);
                    velocity.y = 0;
                    break;
                }
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && (onGround || onPlatform)) {
            velocity.y = -jumpSpeed;
        }


    }

private:
    float moveSpeed;
    float jumpSpeed;
};

#endif // HERO_H
