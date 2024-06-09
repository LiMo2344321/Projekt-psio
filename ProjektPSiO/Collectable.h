#ifndef COLLECTABLE_H
#define COLLECTABLE_H

#include <SFML/Graphics.hpp>
#include <vector>

class Collectable {
public:
    Collectable(const std::vector<sf::Texture>& textures, float x, float y)
        : textures(textures), currentFrame(0), animationTime(sf::seconds(0.1f)), elapsedTime(sf::Time::Zero), collected(false) {
        sprite.setPosition(x, y);
        sprite.setTexture(textures[0]);
        sprite.setScale(2.0f, 2.0f);
    }

    virtual ~Collectable() = default;

    void update(sf::Time deltaTime) {
        if (collected) return;
        elapsedTime += deltaTime;
        if (elapsedTime >= animationTime) {
            elapsedTime -= animationTime;
            currentFrame = (currentFrame + 1) % textures.size();
            sprite.setTexture(textures[currentFrame]);
        }
    }

    void collect() {
        collected = true;
        if (!textures.empty()) {
            sprite.setTexture(textures[0]); 
        }
    }

    bool isCollected() const {
        return collected;
    }

    sf::Sprite& getSprite() {
        return sprite;
    }

    void resetAnimation(float x, float y) {
        collected = false;
        currentFrame = 0;
        elapsedTime = sf::Time::Zero;
        sprite.setPosition(x,y);
        if (!textures.empty()) {
            sprite.setTexture(textures[0]); 
        }
    }

private:
    sf::Sprite sprite;
    std::vector<sf::Texture> textures;
    unsigned int currentFrame;
    sf::Time animationTime;
    sf::Time elapsedTime;
    bool collected;
};

#endif