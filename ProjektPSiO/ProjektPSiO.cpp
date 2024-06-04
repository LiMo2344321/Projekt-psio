#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Map.h"


int main() {
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Projekt", sf::Style::Titlebar | sf::Style::Close);

    const float gravity = 0.0035f;
    int groundHeight = window.getSize().y - 200;
    sf::Vector2f velocity(0, 0);

    sf::Texture texture;
    if (!texture.loadFromFile("idle.png")) {
        std::cerr << "Error loading texture" << std::endl;
        return -1;
    }

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(0, 0);
    sprite.setScale(3.0f, 3.0f);

    sf::RectangleShape floor(sf::Vector2f(window.getSize().x, 200));
    floor.setFillColor(sf::Color::Green);
    floor.setPosition(0, groundHeight);

    sf::Texture shipTexture;
    if (!shipTexture.loadFromFile("Ship1.png")) {
        std::cerr << "Error loading ship texture" << std::endl;
        return -1;
    }

    sf::Texture mastTexture;
    if (!mastTexture.loadFromFile("Maszt.png")) {
        std::cerr << "Error loading mast texture" << std::endl;
        return -1;
    }

    sf::Texture flagTexture;
    if (!flagTexture.loadFromFile("Flag1.png")) {
        std::cerr << "Error loading flag texture" << std::endl;
        return -1;
    }

    std::vector<sf::RectangleShape> platforms;
    std::vector<sf::Sprite> backgroundElements;
    int currentMap = 1;
    loadMap(currentMap, platforms, backgroundElements, groundHeight, shipTexture, mastTexture, flagTexture);

    float moveSpeed = 0.3f, jumpSpeed = 1.5f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            velocity.x = moveSpeed;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            velocity.x = -moveSpeed;
        else
            velocity.x = 0;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
            (sprite.getPosition().y + sprite.getGlobalBounds().height >= groundHeight ||
                std::any_of(platforms.begin(), platforms.end(), [&sprite](const sf::RectangleShape& platform) {
                    return (sprite.getPosition().x + sprite.getGlobalBounds().width > platform.getPosition().x &&
                        sprite.getPosition().x < platform.getPosition().x + platform.getSize().x &&
                        sprite.getPosition().y + sprite.getGlobalBounds().height == platform.getPosition().y);
                    }))) {
            velocity.y = -jumpSpeed;
        }

        if (sprite.getPosition().y + sprite.getGlobalBounds().height < groundHeight || velocity.y < 0) {
            velocity.y += gravity;
        }
        else {
            sprite.setPosition(sprite.getPosition().x, groundHeight - sprite.getGlobalBounds().height);
            velocity.y = 0;
        }

        for (auto& platform : platforms) {
            if (sprite.getGlobalBounds().intersects(platform.getGlobalBounds())) {
                if (sprite.getPosition().y + sprite.getGlobalBounds().height - velocity.y <= platform.getPosition().y) {
                    sprite.setPosition(sprite.getPosition().x, platform.getPosition().y - sprite.getGlobalBounds().height);
                    velocity.y = 0;
                }
                else if (sprite.getPosition().x + sprite.getGlobalBounds().width - velocity.x <= platform.getPosition().x) {
                    sprite.setPosition(platform.getPosition().x - sprite.getGlobalBounds().width, sprite.getPosition().y);
                    velocity.x = 0;
                }
                else if (sprite.getPosition().x - velocity.x >= platform.getPosition().x + platform.getSize().x) {
                    sprite.setPosition(platform.getPosition().x + platform.getSize().x, sprite.getPosition().y);
                    velocity.x = 0;
                }
            }
        }

        sprite.move(velocity.x, velocity.y);

        if (sprite.getPosition().x > window.getSize().x && currentMap == 1) {
            currentMap++;
            loadMap(currentMap, platforms, backgroundElements, groundHeight, shipTexture, mastTexture, flagTexture);
            sprite.setPosition(0, sprite.getPosition().y);
        }
        else if (sprite.getPosition().x > window.getSize().x && currentMap == 2) {
            currentMap++;
            loadMap(currentMap, platforms, backgroundElements, groundHeight, shipTexture, mastTexture, flagTexture);
            sprite.setPosition(0, sprite.getPosition().y);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && currentMap == 2 && sprite.getPosition().x > 1024 && sprite.getPosition().x < 1204) {
            currentMap = 3;
            loadMap(currentMap, platforms, backgroundElements, groundHeight, shipTexture, mastTexture, flagTexture);
            sprite.setPosition(window.getSize().x - sprite.getGlobalBounds().width, 0); 
        }

        if (currentMap == 1 && sprite.getPosition().x < 0) {
            sprite.setPosition(0, sprite.getPosition().y);
        }
        else if ((currentMap == 2 || currentMap == 3) && sprite.getPosition().x < 0) {
            sprite.setPosition(0, sprite.getPosition().y);
        }
        else if (currentMap == 2 && sprite.getPosition().x + sprite.getGlobalBounds().width > window.getSize().x) {
            sprite.setPosition(window.getSize().x - sprite.getGlobalBounds().width, sprite.getPosition().y);
        }
        else if (currentMap == 3 && sprite.getPosition().x + sprite.getGlobalBounds().width > window.getSize().x) {
            sprite.setPosition(window.getSize().x - sprite.getGlobalBounds().width, sprite.getPosition().y);
        }

        window.clear(sf::Color(0, 240, 255));
        for (const auto& element : backgroundElements) {
            window.draw(element);
        }
        window.draw(sprite);
        window.draw(floor);
        for (const auto& platform : platforms) {
            window.draw(platform);
        }
        window.display();
    }

    return 0;
}
