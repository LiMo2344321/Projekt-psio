#ifndef CHEST_H
#define CHEST_H

#include <SFML/Graphics.hpp>
#include <vector>

class Chest {
public:
    Chest(const sf::Texture& closedTexture, const std::vector<sf::Texture>& openTextures, float x, float y)
        : closedTexture(closedTexture), openTextures(openTextures), currentFrame(0), animationTime(sf::seconds(0.1f)), elapsedTime(sf::Time::Zero), isOpen(false) {
        sprite.setPosition(x, y);
        sprite.setTexture(closedTexture);
        sprite.setScale(3.0f, 3.0f);
    }

    void update(sf::Time deltaTime) {
        if (isOpen) {
            elapsedTime += deltaTime;
            if (elapsedTime >= animationTime) {
                elapsedTime -= animationTime;
                currentFrame++;
                if (currentFrame < openTextures.size()) {
                    sprite.setTexture(openTextures[currentFrame]);
                }
                else {
                    isOpen = false;
                }
            }
        }
    }

    void open() {
        if (!isOpen) {
            isOpen = true;
            currentFrame = 0;
            elapsedTime = sf::Time::Zero;
        }
    }

    bool isOpened() const {
        return isOpen;
    }

    sf::Sprite& getSprite() {
        return sprite;
    }

private:
    sf::Sprite sprite;
    sf::Texture closedTexture;
    std::vector<sf::Texture> openTextures;
    unsigned int currentFrame;
    sf::Time animationTime;
    sf::Time elapsedTime;
    bool isOpen;
};

#endif