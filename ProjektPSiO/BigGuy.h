#ifndef BIGGUY_H
#define BIGGUY_H

#include "Enemy.h"

class BigGuy : public Enemy {
public:
    BigGuy(const sf::Texture& texture, float gravity, float speed)
        : Enemy(gravity), speed(speed), movingRight(true), detectionRange(300.0f) {  // Ustawienie zakresu wykrywania na 300 pikseli
        sprite.setTexture(texture);
        sprite.setScale(2.0f, 2.0f);
    }

    void update(const sf::RectangleShape& platform, const sf::Sprite& heroSprite) {
        float heroPositionX = heroSprite.getPosition().x;
        float bigGuyPositionX = sprite.getPosition().x;
        float platformStartX = platform.getPosition().x;
        float platformEndX = platform.getPosition().x + platform.getSize().x;

        // SprawdŸ, czy postaæ gracza znajduje siê w zasiêgu wykrywania
        if (std::abs(heroPositionX - bigGuyPositionX) < detectionRange) {
            // Poruszaj siê w kierunku postaci gracza
            if (heroPositionX > bigGuyPositionX && (bigGuyPositionX + sprite.getGlobalBounds().width) < platformEndX) {
                sprite.move(speed, 0);
            }
            else if (heroPositionX < bigGuyPositionX && bigGuyPositionX > platformStartX) {
                sprite.move(-speed, 0);
            }
        }

        // Upewnij siê, ¿e BigGuy nie spada z platformy
        if (sprite.getPosition().x < platformStartX) {
            sprite.setPosition(platformStartX, sprite.getPosition().y);
        }
        if (sprite.getPosition().x + sprite.getGlobalBounds().width > platformEndX) {
            sprite.setPosition(platformEndX - sprite.getGlobalBounds().width, sprite.getPosition().y);
        }
    }

private:
    float speed;
    bool movingRight;
    float detectionRange;  // Zakres wykrywania postaci gracza
};

#endif
