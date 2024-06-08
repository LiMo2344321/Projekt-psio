#ifndef HERO_H
#define HERO_H

#include "Postac.h"
#include <vector>
#include <algorithm>
#include <SFML/Graphics.hpp>

class Hero : public Postac {
public:
    Hero(const sf::Texture& texture, float gravity, float moveSpeed, float jumpSpeed)
        : Postac(gravity), moveSpeed(moveSpeed), jumpSpeed(jumpSpeed), currentTextureIndex(0), stepsSinceLastSpriteChange(0), idleTexture(texture) {
        sprite.setTexture(idleTexture);
        sprite.setScale(3.0f, 3.0f); // Skaluje sprite hero
        adjustOriginAndScale();
    }

    void handleInput(const std::vector<sf::RectangleShape>& platforms, float groundHeight) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            velocity.x = moveSpeed;
            direction = Direction::Right;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            velocity.x = -moveSpeed;
            direction = Direction::Left;
        }
        else {
            velocity.x = 0;
        }

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

    void update(float groundHeight) override {
        applyGravity(groundHeight);
        sprite.move(velocity);
        updateAnimation();
    }

    void addRunTexture(const sf::Texture& texture) {
        runTextures.push_back(texture);
    }

private:
    enum class Direction { None, Left, Right };
    Direction direction = Direction::None;
    std::vector<sf::Texture> runTextures;
    sf::Texture idleTexture;
    float moveSpeed;
    float jumpSpeed;
    size_t currentTextureIndex;
    int stepsSinceLastSpriteChange;

    void updateAnimation() {
        const int stepsBetweenSprites = 80; // Zwiêkszona liczba kroków miêdzy zmianami sprite'a

        if (velocity.x != 0 && !runTextures.empty()) {
            stepsSinceLastSpriteChange++;
            if (stepsSinceLastSpriteChange >= stepsBetweenSprites) {
                currentTextureIndex = (currentTextureIndex + 1) % runTextures.size();
                sprite.setTexture(runTextures[currentTextureIndex]);
                adjustOriginAndScale();
                stepsSinceLastSpriteChange = 0;
            }
        }
        else {
            sprite.setTexture(idleTexture);
            adjustOriginAndScale();
        }
    }

    void adjustOriginAndScale() {
        float halfWidth = sprite.getLocalBounds().width / 2.0f;
        if (direction == Direction::Left) {
            sprite.setOrigin(halfWidth, 0); // Origin w œrodku sprite'a
            sprite.setScale(-3.0f, 3.0f); // Skaluje w lewo
        }
        else {
            sprite.setOrigin(halfWidth, 0); // Origin w œrodku sprite'a
            sprite.setScale(3.0f, 3.0f); // Skaluje w prawo
        }
    }
};

#endif // HERO_H
