#ifndef CRAB_H
#define CRAB_H

#include "Enemy.h"

class Crab : public Enemy {
public:
    Crab(const sf::Texture& texture, float gravity, float speed)
        : Enemy(gravity), speed(speed), movingRight(true) {
        sprite.setTexture(texture);
        sprite.setScale(3.0f, 3.0f);
    }

    void update(const sf::RectangleShape& platform) {
        if (movingRight) {
            sprite.move(speed-0.05f, 0);
            if (sprite.getPosition().x + sprite.getGlobalBounds().width > platform.getPosition().x + platform.getSize().x) {
                movingRight = false;
            }
        }
        else {
            sprite.move(-speed+0.05f, 0);
            if (sprite.getPosition().x < platform.getPosition().x) {
                movingRight = true;
            }
        }
    }

private:
    float speed;
    bool movingRight;
};

#endif // CRAB_H
