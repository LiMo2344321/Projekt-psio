#ifndef HERO_H
#define HERO_H

#include "Postac.h"
#include <vector>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <iostream> // Dodano, aby u�y� std::cerr

class Hero : public Postac {
public:
    enum class State { Idle, Run, Jump };

    Hero(const sf::Texture& texture, float gravity, float moveSpeed, float jumpSpeed)
        : Postac(gravity), moveSpeed(moveSpeed), jumpSpeed(jumpSpeed), currentTextureIndex(0), elapsedTime(0), state(State::Idle), health(3) {
        idleTextures.push_back(texture);
        sprite.setTexture(idleTextures[0]);
        sprite.setScale(3.0f, 3.0f); // Skaluje sprite hero
        adjustOriginAndScale();

        if (!healthBarTexture.loadFromFile("healthbar.png")) {
            std::cerr << "Error loading health bar texture" << std::endl;
        }
        if (!heartTexture.loadFromFile("heart.png")) {
            std::cerr << "Error loading heart texture" << std::endl;
        }

        healthBar.setTexture(healthBarTexture);
        healthBar.setPosition(10.0f, 10.0f); 
        healthBar.setScale(1.0f, 1.0f);
        heart.setTexture(heartTexture);
        heart.setScale(1.0f, 1.0f); 
    }

    void handleInput(const std::vector<sf::RectangleShape>& platforms, float groundHeight) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            velocity.x = moveSpeed;
            direction = Direction::Right;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { state = State::Jump; }
            else {
                state = State::Run;
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            velocity.x = -moveSpeed;
            direction = Direction::Left;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { state = State::Jump; }
            else {
                state = State::Run;
            }
        }
        else {
            velocity.x = 0;
            state = State::Idle;
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

                if (heroBottom > platformTop && heroBottom < platformTop + 10.0f) {
                    onPlatform = true;
                    sprite.setPosition(sprite.getPosition().x, platformTop - heroBounds.height);
                    velocity.y = 0;
                    break;
                }
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && (onGround || onPlatform)) {
            velocity.y = -jumpSpeed;
            state = State::Jump; // Ustaw stan na skok
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

    void addIdleTexture(const sf::Texture& texture) {
        idleTextures.push_back(texture);
    }

    void addJumpTexture(const sf::Texture& texture) {
        jumpTextures.push_back(texture);
    }

    void setFps(int fps) {
        this->fps = fps;
    }

    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
        drawHealthBar(window);
    }

    void takeDamage() {
        if (health > 0) {
            health--;
        }
    }

    int getHealth() const {
        return health;
    }

    bool isAlive() const {
        return health > 0;
    }

    void resetHealth() {
        health = 3;
    }

    void kill() {
        health = 0;
    }

private:
    enum class Direction { None, Left, Right };
    Direction direction = Direction::None;
    std::vector<sf::Texture> runTextures;
    std::vector<sf::Texture> idleTextures;
    std::vector<sf::Texture> jumpTextures;
    float moveSpeed;
    float jumpSpeed;
    size_t currentTextureIndex;
    float elapsedTime;
    int fps = 20; // Default FPS for animation
    State state;
    int health;

    sf::Texture healthBarTexture;
    sf::Texture heartTexture;
    sf::Sprite healthBar;
    sf::Sprite heart;

    void updateAnimation() {
        elapsedTime += clock.restart().asSeconds();
        float frameDuration = 1.0f / fps;

        if (elapsedTime >= frameDuration) {
            elapsedTime = 0;

            switch (state) {
            case State::Idle:
                if (!idleTextures.empty()) {
                    currentTextureIndex = (currentTextureIndex + 1) % idleTextures.size();
                    sprite.setTexture(idleTextures[currentTextureIndex]);
                }
                break;
            case State::Run:
                if (!runTextures.empty()) {
                    currentTextureIndex = (currentTextureIndex + 1) % runTextures.size();
                    sprite.setTexture(runTextures[currentTextureIndex]);
                }
                break;
            case State::Jump:
                if (!jumpTextures.empty()) {
                    currentTextureIndex = (currentTextureIndex + 1) % jumpTextures.size();
                    sprite.setTexture(jumpTextures[currentTextureIndex]);
                }
                break;
            }
            adjustOriginAndScale();
        }
    }

    void adjustOriginAndScale() {
        float halfWidth = sprite.getLocalBounds().width / 2.0f;
        if (direction == Direction::Left) {
            sprite.setOrigin(halfWidth, 0); // Origin w �rodku sprite'a
            sprite.setScale(-3.0f, 3.0f); // Skaluje w lewo
        }
        else {
            sprite.setOrigin(halfWidth, 0); // Origin w �rodku sprite'a
            sprite.setScale(3.0f, 3.0f); // Skaluje w prawo
        }
    }

    void drawHealthBar(sf::RenderWindow& window) {
        window.draw(healthBar);
        for (int i = 0; i < health; ++i) {
            heart.setPosition(50.0f + i * (heart.getGlobalBounds().width + 5.0f), 32.0f); // Position hearts within health bar
            window.draw(heart);
        }
    }

    sf::Clock clock;
};

#endif 
