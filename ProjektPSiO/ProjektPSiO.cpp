#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Functions.h"
#include "Hero.h"
#include "Cannon.h"

int main() {
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Projekt", sf::Style::Titlebar | sf::Style::Close);

    const float gravity = 0.0035f;
    int groundHeight = window.getSize().y - 200;
    int currentGroundHeight = groundHeight;

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

    sf::Texture cannonballTexture;
    if (!cannonballTexture.loadFromFile("cball.png")) {
        std::cerr << "Error loading cannonball texture" << std::endl;
        return -1;
    }

    Cannon cannon(gravity, cannonballTexture);
    cannon.setPosition(650, groundHeight - cannon.getGlobalBounds().height);

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

        if (currentMap == 1) {
            currentGroundHeight = groundHeight;
        }
        else if (currentMap == 2) {
            currentGroundHeight = window.getSize().y + 200;
        }
        else if (currentMap == 3) {
            currentGroundHeight = groundHeight;
        }

        hero.handleInput(platforms, currentGroundHeight);
        hero.update(currentGroundHeight);
        handleCollisions(hero, platforms);

        cannon.update(currentGroundHeight);
        handleCollisions(cannon, platforms);

        for (auto& cannonball : cannon.getCannonballs()) {
            if (cannonball.getGlobalBounds().intersects(hero.getGlobalBounds())) {
                // Handle hero hit by cannonball
                // For now, let's just reset hero's position
                hero.setPosition(0, 0);
            }
            for (const auto& platform : platforms) {
                if (cannonball.getGlobalBounds().intersects(platform.getGlobalBounds())) {
                    // Remove cannonball on platform hit
                    cannon.getCannonballs().erase(std::remove(cannon.getCannonballs().begin(), cannon.getCannonballs().end(), cannonball), cannon.getCannonballs().end());
                    break;
                }
            }
        }

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

        if (currentMap == 1) {
            window.draw(cannon.getSprite());
            window.draw(floor);
        }

        if (currentMap == 3) {
            window.draw(floor);
        }

        for (const auto& platform : platforms) {
            window.draw(platform);
        }

        for (const auto& cannonball : cannon.getCannonballs()) {
            window.draw(cannonball.getSprite());
        }

        window.display();
    }

    return 0;
}
