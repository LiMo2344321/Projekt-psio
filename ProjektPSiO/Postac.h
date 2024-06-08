#ifndef POSTAC_H
#define POSTAC_H

#include <SFML/Graphics.hpp>

class Postac {
public:
    Postac(float gravity)
        : gravity(gravity), velocity(0, 0) {
        sprite.setScale(3.0f, 3.0f);
        adjustOrigin();
    }

    virtual void update(float groundHeight) {
        applyGravity(groundHeight);
        sprite.move(velocity);
    }

    void setPosition(float x, float y) {
        sprite.setPosition(x, y);
    }

    sf::Vector2f getPosition() const {
        return sprite.getPosition();
    }

    sf::FloatRect getGlobalBounds() const {
        return sprite.getGlobalBounds();
    }

    void setVelocity(const sf::Vector2f& vel) {
        velocity = vel;
    }
    void setVelx(float x) {
        velocity.x = x;
    }

    void setVely(float y) {
        velocity.y = y;
    }

    sf::Vector2f getVelocity() const {
        return velocity;
    }

    void setTexture(const sf::Texture& texture) {
        sprite.setTexture(texture);
    }

    const sf::Sprite& getSprite() const {
        return sprite;
    }

protected:
    sf::Sprite sprite;
    float gravity;
    sf::Vector2f velocity;

    void applyGravity(float groundHeight) {
        if (sprite.getPosition().y + sprite.getGlobalBounds().height < groundHeight || velocity.y < 0) {
            velocity.y += gravity;
        }
        else {
            sprite.setPosition(sprite.getPosition().x, groundHeight - sprite.getGlobalBounds().height);
            velocity.y = 0;
        }
    }

    void adjustOrigin() {
        sprite.setOrigin(sprite.getLocalBounds().width / 2.0f, 0);  // Origin w œrodku sprite'a
    }
};

#endif 
