#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Map.h"
#include "Hero.h"
#include "Cannon.h"

void handleCollisions(Postac& character, const std::vector<sf::RectangleShape>& platforms) {
    for (const auto& platform : platforms) {
        if (character.getGlobalBounds().intersects(platform.getGlobalBounds())) {
            // Sprawdzanie kolizji od góry
            if (character.getPosition().y + character.getGlobalBounds().height - character.getVelocity().y <= platform.getPosition().y) {
                character.setPosition(character.getPosition().x, platform.getPosition().y - character.getGlobalBounds().height);
                character.setVelocity({ character.getVelocity().x, 0 });
            }
            // Sprawdzanie kolizji od dołu
            else if (character.getPosition().y - character.getVelocity().y >= platform.getPosition().y + platform.getSize().y) {
                character.setPosition(character.getPosition().x, platform.getPosition().y + platform.getSize().y);
                character.setVelocity({ character.getVelocity().x, 0 });
            }
            // Sprawdzanie kolizji z lewej strony
            else if (character.getPosition().x + character.getGlobalBounds().width - character.getVelocity().x <= platform.getPosition().x) {
                character.setPosition(platform.getPosition().x - character.getGlobalBounds().width, character.getPosition().y);
                character.setVelocity({ 0, character.getVelocity().y });
            }
            // Sprawdzanie kolizji z prawej strony
            else if (character.getPosition().x - character.getVelocity().x >= platform.getPosition().x + platform.getSize().x) {
                character.setPosition(platform.getPosition().x + platform.getSize().x, character.getPosition().y);
                character.setVelocity({ 0, character.getVelocity().y });
            }
        }
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Projekt", sf::Style::Titlebar | sf::Style::Close);

    const float gravity = 0.0035f;
    int groundHeight = window.getSize().y - 200;

    sf::Texture heroTexture;
    if (!heroTexture.loadFromFile("idle.png")) {
        std::cerr << "Error loading texture" << std::endl;
        return -1;
    }

    Hero hero(heroTexture, gravity, 0.3f, 1.5f);
    hero.setPosition(0, 0);

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

    Cannon cannon(gravity);
    cannon.setPosition(100, groundHeight - cannon.getGlobalBounds().height);

    std::vector<sf::RectangleShape> platforms;
    std::vector<sf::Sprite> backgroundElements;
    int currentMap = 1;
    loadMap(currentMap, platforms, backgroundElements, groundHeight, shipTexture, mastTexture, flagTexture);

    if (currentMap == 1) {
        backgroundElements.push_back(cannon.getSprite());
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        hero.handleInput(platforms, groundHeight);
        hero.update(groundHeight);
        handleCollisions(hero, platforms);

        cannon.update(groundHeight);
        handleCollisions(cannon, platforms);

        if (hero.getPosition().x > window.getSize().x && currentMap == 1) {
            currentMap++;
            loadMap(currentMap, platforms, backgroundElements, groundHeight, shipTexture, mastTexture, flagTexture);
            hero.setPosition(0, hero.getPosition().y);
        }
        else if (hero.getPosition().x > window.getSize().x && currentMap == 2) {
            currentMap++;
            loadMap(currentMap, platforms, backgroundElements, groundHeight, shipTexture, mastTexture, flagTexture);
            hero.setPosition(0, hero.getPosition().y);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && currentMap == 2 && hero.getPosition().x > 1024 && hero.getPosition().x < 1204) {
            currentMap = 3;
            loadMap(currentMap, platforms, backgroundElements, groundHeight, shipTexture, mastTexture, flagTexture);
            hero.setPosition(window.getSize().x - hero.getGlobalBounds().width, 0);
        }

        if (currentMap == 1 && hero.getPosition().x < 0) {
            hero.setPosition(0, hero.getPosition().y);
        }
        else if ((currentMap == 2 || currentMap == 3) && hero.getPosition().x < 0) {
            hero.setPosition(0, hero.getPosition().y);
        }
        else if (currentMap == 2 && hero.getPosition().x + hero.getGlobalBounds().width > window.getSize().x) {
            hero.setPosition(window.getSize().x - hero.getGlobalBounds().width, hero.getPosition().y);
        }
        else if (currentMap == 3 && hero.getPosition().x + hero.getGlobalBounds().width > window.getSize().x) {
            hero.setPosition(window.getSize().x - hero.getGlobalBounds().width, hero.getPosition().y);
        }

        window.clear(sf::Color(0, 240, 255));
        for (const auto& element : backgroundElements) {
            window.draw(element);
        }
        window.draw(hero.getSprite());
        window.draw(cannon.getSprite());
        window.draw(floor);
        for (const auto& platform : platforms) {
            window.draw(platform);
        }
        window.display();
    }

    return 0;
}
