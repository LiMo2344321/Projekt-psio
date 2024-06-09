#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Functions.h"
#include "Hero.h"
#include "Cannon.h"
#include "Crab.h"
#include "BigGuy.h"
#include "Pirate.h"
#include "Captain.h"
#include "Key.h"


int main() {
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Projekt", sf::Style::Titlebar | sf::Style::Close);

    const float gravity = 0.0035f;
    int groundHeight = window.getSize().y - 200;
    int currentGroundHeight = groundHeight;

    std::vector <sf::Texture> idle(5);
    for (int i = 0; i < 5; i++) {
        if (!idle[i].loadFromFile("idle" + std::to_string(i + 1) + ".png")) {
            std::cerr << "Error loading idle texture " << i + 1 << std::endl;
            return -1;
        }
    }

    std::vector <sf::Texture> run(6);
    for (int i = 0; i < 6; i++) {
        if (!run[i].loadFromFile("run" + std::to_string(i + 1) + ".png")) {
            std::cerr << "Error loading run texture " << i + 1 << std::endl;
            return -1;
        }
    }

    sf::Texture jump;
    jump.loadFromFile("jump.png");

    Hero hero(idle[0], gravity, 0.3f, 1.5f);

    for (int i = 0; i < 5; i++) {
        hero.addIdleTexture(idle[i]);
    }

    for (int i = 0; i < 6; i++) {
        hero.addRunTexture(run[i]);
    }
    hero.addJumpTexture(jump);

    hero.setFps(20);
    hero.setPosition(100, groundHeight);


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

    sf::Texture pirateTexture;
    if (!pirateTexture.loadFromFile("pirate.png")) {
        std::cerr << "Error loading pirate texture" << std::endl;
        return -1;
    }

    sf::Texture captainTexture;
    if (!captainTexture.loadFromFile("captain.png")) {
        std::cerr << "Error loading captain texture" << std::endl;
        return -1;
    }


    sf::RectangleShape floor(sf::Vector2f(window.getSize().x, 200));
    floor.setFillColor(sf::Color::Green);
    floor.setPosition(0, groundHeight);

    Cannon cannon(gravity, cannonballTexture);
    cannon.setPosition(650, groundHeight - cannon.getGlobalBounds().height);


    std::vector <sf::Texture> cshoot(6);
    for (int i = 0; i < 6; i++) {
        if (!cshoot[i].loadFromFile("cshoot" + std::to_string(i + 1) + ".png")) {
            std::cerr << "Error loading cshoot texture " << i + 1 << std::endl;
            return -1;
        }
    }

    for (int i = 0; i < 6; i++) {
        cannon.addShootTexture(cshoot[i]);
    }



    // Load crab run textures
    std::vector <sf::Texture> crabRun(6);
    for (int i = 0; i < 6; i++) {
        if (!crabRun[i].loadFromFile("crabrun" + std::to_string(i + 1) + ".png")) {
            std::cerr << "Error loading crab run texture " << i + 1 << std::endl;
            return -1;
        }
    }

    // Initialize crab with gravity, speed, and animation time
    Crab crab(gravity, 0.03f, 0.2f);
    crab.setPosition(1050, 329);

    // Add run textures to crab
    for (int i = 0; i < 6; i++) {
        crab.addRunTexture(crabRun[i]);
    }

    std::vector<sf::Texture> bigguyidle(36);
    std::vector<sf::Texture> bigguyrun(8);
    std::vector<sf::Texture> bigguyattack(10);
    for (int i = 0; i < 36; ++i) {
        if (!bigguyidle[i].loadFromFile("guyidle" + std::to_string(i + 1) + ".png")) {
            std::cerr << "Error loading idle texture " << i + 1 << std::endl;
            return -1;
        }
    }

    for (int i = 0; i < 8; ++i) {
        if (!bigguyrun[i].loadFromFile("guyrun" + std::to_string(i + 1) + ".png")) {
            std::cerr << "Error loading run texture " << i + 1 << std::endl;
            return -1;
        }
    }

    for (int i = 0; i < 10; ++i) {
        if (!bigguyattack[i].loadFromFile("bigguyattack" + std::to_string(i + 1) + ".png")) {
            std::cerr << "Error loading attack texture " << i + 1 << std::endl;
            return -1;
        }
    }



    BigGuy guy1(bigguyidle, bigguyrun, bigguyattack, gravity, 0.2f);
    BigGuy guy2(bigguyidle, bigguyrun, bigguyattack, gravity, 0.2f);
    guy1.setPosition(1002, 250 - guy1.getSprite().getGlobalBounds().height);
    guy2.setPosition(1502, groundHeight - 396 - guy2.getSprite().getGlobalBounds().height);

    Pirate pirate(pirateTexture, gravity, 0.3f);
    pirate.setPosition(1000, 150 - pirate.getSprite().getGlobalBounds().height);

    Captain captain(captainTexture, gravity, 0.1f);
    captain.setPosition(800, groundHeight - 280 - captain.getSprite().getGlobalBounds().height);

    std::vector<sf::Texture> keyTextures(8);
    for (int i = 0; i < 8; ++i) {
        if (!keyTextures[i].loadFromFile("key" + std::to_string(i + 1) + ".png")) {
            std::cerr << "Error loading key texture " << i + 1 << std::endl;
            return -1;
        }
    }
    Key key(keyTextures, 1654, 440);


    std::vector<sf::RectangleShape> platforms;
    std::vector<sf::Sprite> backgroundElements;
    std::vector<sf::Sprite> spikes;
    int currentMap = 1;
    loadMap(currentMap, platforms, backgroundElements, spikes, groundHeight, shipTexture, mastTexture, flagTexture, spikeTexture);

    sf::Clock damageClock;
    sf::Clock clock;
    bool recentlyDamaged = false;
    sf::Time lastDamageTime = sf::Time::Zero;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        sf::Time deltaTime = clock.restart();
        sf::Time currentTime = damageClock.getElapsedTime();  // Zmierz czas od ostatniego resetu
        if (recentlyDamaged && currentTime.asSeconds() > 1.0f) {  // Reset flagi, jeśli minęła jedna sekunda
            recentlyDamaged = false;
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
            crab.update(platforms[2], deltaTime);  // Update crab movement
            handleCollisions(crab, platforms);
            //if (crab.getSprite().getGlobalBounds().intersects(hero.getSprite().getGlobalBounds())) {
            //    hero.setPosition(0, 0); //przegrana
            //}
        }

        bool heroDamaged = false;

        if (currentMap == 1 || currentMap == 3) {
            for (const auto& spike : spikes) {
                if (spike.getGlobalBounds().intersects(hero.getSprite().getGlobalBounds())) {
                    hero.kill(); // Bohater natychmiast umiera
                    hero.setPosition(100, 0); // Resetuje pozycję bohatera
                    hero.resetHealth(); // Resetuje życie bohatera
                    break; // Przerwanie pętli po kolizji z kolcami
                }
            }
        }

        if (currentMap == 2) {
            guy1.update(platforms[3], hero.getSprite(), deltaTime);
            guy2.update(platforms[1], hero.getSprite(), deltaTime);
            key.update(deltaTime);

            handleCollisions(guy1, platforms);
            handleCollisions(guy2, platforms);

            if (guy1.getisAttacking() && guy1.getSprite().getGlobalBounds().intersects(hero.getSprite().getGlobalBounds())) {
                if (!recentlyDamaged || (currentTime - lastDamageTime > sf::seconds(1.0f))) {
                    hero.takeDamage(); // Zadanie obrażeń bohaterowi
                    heroDamaged = true;
                    lastDamageTime = currentTime;
                    recentlyDamaged = true;
                    damageClock.restart();
                }
            }

            if (guy2.getisAttacking() && guy2.getSprite().getGlobalBounds().intersects(hero.getSprite().getGlobalBounds())) {
                if (!recentlyDamaged || (currentTime - lastDamageTime > sf::seconds(1.0f))) {
                    hero.takeDamage(); // Zadanie obrażeń bohaterowi
                    heroDamaged = true;
                    lastDamageTime = currentTime;
                    recentlyDamaged = true;
                    damageClock.restart();
                }
            }

            if (!key.isCollected() && key.getSprite().getGlobalBounds().intersects(hero.getSprite().getGlobalBounds())) {
                key.collect();
                hero.pickUpKey();
            }

            if (hero.getPosition().y > window.getSize().y) {
                hero.kill();
                hero.setPosition(100, 0);
                hero.resetHealth();

            }
        }

        if (currentMap == 3) {

            pirate.update(platforms[1]);
            handleCollisions(pirate, platforms);

            captain.update(platforms[5]);
            handleCollisions(captain, platforms);

        }


        for (const auto& cannonball : cannon.getCannonballs()) {
            if (cannonball.getGlobalBounds().intersects(hero.getSprite().getGlobalBounds())) {
                if (recentlyDamaged && (clock.getElapsedTime().asSeconds() - lastDamageTime.asSeconds() > 0.5)) {
                    recentlyDamaged = false;
                }
                if (!recentlyDamaged) {
                    hero.takeDamage(); // Przegrana, zabierz jedno życie
                    heroDamaged = true;
                    lastDamageTime = currentTime;
                    recentlyDamaged = true;
                    damageClock.restart();

                }
            }
            for (const auto& platform : platforms) {
                if (cannonball.getGlobalBounds().intersects(platform.getGlobalBounds())) {
                    cannon.getCannonballs().erase(std::remove(cannon.getCannonballs().begin(), cannon.getCannonballs().end(), cannonball), cannon.getCannonballs().end());
                    break;
                }
            }
        }



        if (heroDamaged && !hero.isAlive()) {
            hero.setPosition(100, 0); // Resetuj pozycję bohatera przy zerowych życiach
            hero.resetHealth(); // Resetuj życie bohatera
            hero.setHasKey(false); // Upewnij się, że bohater nie ma klucza
            key.resetAnimation(1654, 440); // Resetuj animację klucza
        }


        if (hero.getPosition().x > window.getSize().x && currentMap == 1) {
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

        if (hero.getHasKey()) {

            sf::Sprite keySprite = key.getSprite();
            keySprite.setPosition(160, 15); // Wybierz odpowiednią pozycję
            window.draw(keySprite);
        }

        window.draw(hero.getSprite());
        hero.draw(window);

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

        if (currentMap == 2) {
            window.draw(guy1.getSprite());
            window.draw(guy2.getSprite());
            if (!key.isCollected()) {
                key.update(deltaTime);
                window.draw(key.getSprite());
            }
        }

        if (currentMap == 3) {
            window.draw(floor);
            window.draw(pirate.getSprite());
            window.draw(captain.getSprite());
        }

        window.display();
    }

    return 0;
}