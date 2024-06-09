#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Functions.h"
#include "Hero.h"
#include "Cannon.h"
#include "Crab.h"

int main() {
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Projekt", sf::Style::Titlebar | sf::Style::Close);

    const float gravity = 0.0035f;
    int groundHeight = window.getSize().y - 200;
    int currentGroundHeight = groundHeight;

    sf::Texture idle1, idle2, idle3, idle4, idle5;
    idle1.loadFromFile("idle1.png");
    idle2.loadFromFile("idle2.png");
    idle3.loadFromFile("idle3.png");
    idle4.loadFromFile("idle4.png");
    idle5.loadFromFile("idle5.png");

    sf::Texture run1, run2, run3, run4, run5, run6;
    run1.loadFromFile("run1.png");
    run2.loadFromFile("run2.png");
    run3.loadFromFile("run3.png");
    run4.loadFromFile("run4.png");
    run5.loadFromFile("run5.png");
    run6.loadFromFile("run6.png");

    sf::Texture jump;
    jump.loadFromFile("jump.png");

    Hero hero(idle1, gravity, 0.3f, 1.5f);
    hero.addIdleTexture(idle1);
    hero.addIdleTexture(idle2);
    hero.addIdleTexture(idle3);
    hero.addIdleTexture(idle4);
    hero.addIdleTexture(idle5);

    hero.addRunTexture(run1);
    hero.addRunTexture(run2);
    hero.addRunTexture(run3);
    hero.addRunTexture(run4);
    hero.addRunTexture(run5);
    hero.addRunTexture(run6);

    hero.addJumpTexture(jump);

    hero.setFps(20);
    hero.setPosition(0, 0);


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

    sf::Texture crabTexture;
    if (!crabTexture.loadFromFile("crabidle.png")) {
        std::cerr << "Error loading crab texture" << std::endl;
        return -1;
    }

    sf::Texture spikeTexture;
    if (!spikeTexture.loadFromFile("Spikes.png")) {
        std::cerr << "Error loading spike texture" << std::endl;
        return -1;
    }

    sf::RectangleShape floor(sf::Vector2f(window.getSize().x, 200));
    floor.setFillColor(sf::Color::Green);
    floor.setPosition(0, groundHeight);

    Cannon cannon(gravity, cannonballTexture);
    cannon.setPosition(650, groundHeight - cannon.getGlobalBounds().height);

    // Załaduj tekstury animacji strzału
    sf::Texture cshoot1, cshoot2, cshoot3, cshoot4, cshoot5, cshoot6;
    cshoot1.loadFromFile("cshoot1.png");
    cshoot2.loadFromFile("cshoot2.png");
    cshoot3.loadFromFile("cshoot3.png");
    cshoot4.loadFromFile("cshoot4.png");
    cshoot5.loadFromFile("cshoot5.png");
    cshoot6.loadFromFile("cshoot6.png");

    cannon.addShootTexture(cshoot1);
    cannon.addShootTexture(cshoot2);
    cannon.addShootTexture(cshoot3);
    cannon.addShootTexture(cshoot4);
    cannon.addShootTexture(cshoot5);
    cannon.addShootTexture(cshoot6);

    Crab crab(crabTexture, gravity, 0.1f);
    crab.setPosition(1050, groundHeight - 480 - crab.getGlobalBounds().height);  // Adjusted for platform3

    std::vector<sf::RectangleShape> platforms;
    std::vector<sf::Sprite> backgroundElements;
    std::vector<sf::Sprite> spikes;
    int currentMap = 1;
    loadMap(currentMap, platforms, backgroundElements, spikes, groundHeight, shipTexture, mastTexture, flagTexture, spikeTexture);

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



        if (currentMap == 1) {
            crab.update(platforms[2]);  // Update crab movement
            handleCollisions(crab, platforms);
            //if (crab.getSprite().getGlobalBounds().intersects(hero.getSprite().getGlobalBounds())) {
            //    hero.setPosition(0, 0); //przegrana
            //}
            for (const auto& spike : spikes) {
                if (spike.getGlobalBounds().intersects(hero.getSprite().getGlobalBounds())) {
                    hero.setPosition(0, 0); //przegrana
                }
            }
           }


        for (const auto& cannonball : cannon.getCannonballs()) {
            if (cannonball.getGlobalBounds().intersects(hero.getGlobalBounds())) {
                hero.setPosition(0, 0); //przegrana
            }
            for (const auto& platform : platforms) {
                if (cannonball.getGlobalBounds().intersects(platform.getGlobalBounds())) {
                    cannon.getCannonballs().erase(std::remove(cannon.getCannonballs().begin(), cannon.getCannonballs().end(), cannonball), cannon.getCannonballs().end());
                    break;
                }
            }
        }

        if (currentMap == 2) {
            if (hero.getPosition().y > window.getSize().y) {
                hero.setPosition(0, 0); //przegrana
            }
        }


        if (currentMap == 3) {
            for (const auto& spike : spikes) {
                if (spike.getGlobalBounds().intersects(hero.getSprite().getGlobalBounds())) {
                    hero.setPosition(window.getSize().x - hero.getGlobalBounds().width, 0); //przegrana
                }
            }
        }



        if (hero.getPosition().x > window.getSize().x && currentMap == 1) {
            currentMap++;
            loadMap(currentMap, platforms, spikes, backgroundElements, groundHeight, shipTexture, mastTexture, flagTexture, spikeTexture);
            hero.setPosition(0, hero.getPosition().y);
        }
        else if (hero.getPosition().x > window.getSize().x && currentMap == 2) {
            currentMap++;
            loadMap(currentMap, platforms, spikes, backgroundElements, groundHeight, shipTexture, mastTexture, flagTexture, spikeTexture);
            hero.setPosition(0, hero.getPosition().y);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && currentMap == 2 && hero.getPosition().x > 1024 && hero.getPosition().x < 1204) {
            currentMap = 3;
            loadMap(currentMap, platforms, spikes, backgroundElements, groundHeight, shipTexture, mastTexture, flagTexture, spikeTexture);
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

        for (const auto& platform : platforms) {
            window.draw(platform);
        }

        for (const auto& spike : spikes) {
            window.draw(spike);
        }

        for (const auto& element : backgroundElements) {
            window.draw(element);
        }


        window.draw(hero.getSprite());
        

        if (currentMap == 1) {
            window.draw(crab.getSprite());
            window.draw(floor);
            window.draw(cannon.getSprite());
            for (const auto& cannonball : cannon.getCannonballs()) {
                window.draw(cannonball.getSprite());
                
            }
            cannon.update(currentGroundHeight);
            handleCollisions(cannon, platforms);
           
        }

        if (currentMap == 3) {
            window.draw(floor);
        
        }

        window.display();
    }

    return 0;
}