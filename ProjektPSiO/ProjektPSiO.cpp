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
#include "Collectable.h"


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

    std::vector <sf::Texture> attack(3);
    for (int i = 0; i < 3; i++) {
        if (!attack[i].loadFromFile("attack" + std::to_string(i + 1) + ".png")) {
            std::cerr << "Error loading attack texture " << i + 1 << std::endl;
            return -1;
        }
    }

    Hero hero(idle[0], gravity, 0.3f, 1.5f);

    for (int i = 0; i < 5; i++) {
        hero.addIdleTexture(idle[i]);
    }

    for (int i = 0; i < 6; i++) {
        hero.addRunTexture(run[i]);
    }
    hero.addJumpTexture(jump);

    for (int i = 0; i < 3; i++) {
        hero.addAttackTexture(attack[i]);
    }

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

    sf::Texture spikeTexture;
    if (!spikeTexture.loadFromFile("Spikes.png")) {
        std::cerr << "Error loading spike texture" << std::endl;
        return -1;
    }

    sf::RectangleShape floor(sf::Vector2f(window.getSize().x, 200));
    floor.setFillColor(sf::Color::Green);
    floor.setPosition(0, groundHeight);

    //armata
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


    //krab
    std::vector <sf::Texture> crabRun(6);
    for (int i = 0; i < 6; i++) {
        if (!crabRun[i].loadFromFile("crabrun" + std::to_string(i + 1) + ".png")) {
            std::cerr << "Error loading crab run texture " << i + 1 << std::endl;
            return -1;
        }
    }

    std::vector <sf::Texture> crabAttack(4);
    for (int i = 0; i < 4; i++) {
        if (!crabAttack[i].loadFromFile("crabattack" + std::to_string(i + 1) + ".png")) {
            std::cerr << "Error loading crab run texture " << i + 1 << std::endl;
            return -1;
        }
    }

    std::vector <sf::Texture> crabAnticipation(3);
    for (int i = 0; i < 3; i++) {
        if (!crabAnticipation[i].loadFromFile("crabanticipation" + std::to_string(i + 1) + ".png")) {
            std::cerr << "Error loading crab anticipation texture " << i + 1 << std::endl;
            return -1;
        }
    }

    std::vector <sf::Texture> crabHit(4);
    for (int i = 0; i < 4; i++) {
        if (!crabHit[i].loadFromFile("crabhit" + std::to_string(i + 1) + ".png")) {
            std::cerr << "Error loading crab hit texture " << i + 1 << std::endl;
            return -1;
        }
    }

    std::vector <sf::Texture> crabDie(5);
    for (int i = 0; i < 5; i++) {
        if (!crabDie[i].loadFromFile("crabdie.png")) {
            std::cerr << "Error loading crab die texture " << std::endl;
            return -1;
        }
    }

    Crab crab(crabRun, crabAttack, crabAnticipation, crabHit, crabDie, gravity, 0.1f);
    crab.setPosition(1050, 329);


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


    std::vector <sf::Texture> pirateattack(12);
    for (int i = 0; i < 12; ++i) {
        if (!pirateattack[i].loadFromFile("pirateattack" + std::to_string(i + 1) + ".png")) {
            std::cerr << "Error loading pirate attack texture " << i + 1 << std::endl;
            return -1;
        }
    }
    std::vector <sf::Texture> pirateidle(34);
    for (int i = 0; i < 34; ++i) {
        if (!pirateidle[i].loadFromFile("pirateidle" + std::to_string(i + 1) + ".png")) {
            std::cerr << "Error loading pirateidle texture " << i + 1 << std::endl;
            return -1;
        }
    }

    std::vector <sf::Texture> piraterun(14);
    for (int i = 0; i < 14; ++i) {
        if (!piraterun[i].loadFromFile("piraterun" + std::to_string(i + 1) + ".png")) {
            std::cerr << "Error loading piraterun texture " << i + 1 << std::endl;
            return -1;
        }
    }

    Pirate pirate(pirateidle, piraterun, pirateattack, gravity, 0.5f);
    pirate.setPosition(1000, 150 - pirate.getSprite().getGlobalBounds().height);

    //kapitan
    std::vector <sf::Texture> captainrun(14);
    for (int i = 0; i < 14; ++i) {
        if (!captainrun[i].loadFromFile("captainrun" + std::to_string(i + 1) + ".png")) {
            std::cerr << "Error loading captainrun texture " << i + 1 << std::endl;
            return -1;
        }
    }

    std::vector <sf::Texture> captainattack(7);
    for (int i = 0; i < 7; ++i) {
        if (!captainattack[i].loadFromFile("captainattack" + std::to_string(i + 1) + ".png")) {
            std::cerr << "Error loading captainattack texture " << i + 1 << std::endl;
            return -1;
        }
    }

    sf::Texture captainhit;
    if (!captainhit.loadFromFile("captainhit.png")) {
        std::cerr << "Error loading captainhit texture " << std::endl;
        return -1;
    }
    sf::Texture captaindie; 
    if (!captaindie.loadFromFile("captaindie.png")) {
        std::cerr << "Error loading captaindie texture " << std::endl;
        return -1;
    }


    Captain captain(captainrun, captainattack, captainhit, captaindie, gravity, 0.1f);
    captain.setPosition(800, groundHeight - 280 - captain.getSprite().getGlobalBounds().height);

    std::vector<sf::Texture> keyTextures(8);
    for (int i = 0; i < 8; ++i) {
        if (!keyTextures[i].loadFromFile("key" + std::to_string(i + 1) + ".png")) {
            std::cerr << "Error loading key texture " << i + 1 << std::endl;
            return -1;
        }
    }

    Collectable key(keyTextures, 1654, 440);


    std::vector <sf::Texture> heartTextures(22);
    for (int i = 0; i < 22; ++i) {
        if (!heartTextures[i].loadFromFile("heart" + std::to_string(i + 1) + ".png")) {
            std::cerr << "Error loading heart texture " << i + 1 << std::endl;
            return -1;
        }
    }


    Collectable heart1(heartTextures, 930, 155);
    Collectable heart2(heartTextures, 30, 355);


    std::vector<sf::RectangleShape> platforms;
    std::vector<sf::Sprite> backgroundElements;
    std::vector<sf::Sprite> spikes;
    int currentMap = 1;
    loadMap(currentMap, platforms, backgroundElements, spikes, groundHeight, shipTexture, mastTexture, flagTexture, spikeTexture);

    sf::Clock damageClock;
    sf::Clock damageClock2;
    sf::Clock clock;
    bool recentlyDamaged = false;
    bool recentlyinflictedDamage = false;
    sf::Time lastDamageTime = sf::Time::Zero;
    sf::Time lastInflictedDamageTime = sf::Time::Zero;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        sf::Time deltaTime = clock.restart();
        sf::Time currentTime = damageClock.getElapsedTime();
        sf::Time currentTime2 = damageClock2.getElapsedTime();

        if (recentlyinflictedDamage && currentTime2.asSeconds() > 1.0f) {
            recentlyinflictedDamage = false;
        }

        if (recentlyDamaged && currentTime.asSeconds() > 1.0f) {
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
        bool heroDamaged = false;

        if (currentMap == 1) {
            if (crab.isCrabAlive()) {
                crab.update(platforms[2], hero.getSprite(), deltaTime);
                handleCollisions(crab, platforms);
                if (crab.getisAttacking() && crab.getSprite().getGlobalBounds().intersects(hero.getSprite().getGlobalBounds())) {
                    if (!recentlyDamaged || (currentTime - lastDamageTime > sf::seconds(1.0f))) {
                        hero.takeDamage();
                        heroDamaged = true;
                        lastDamageTime = currentTime;
                        recentlyDamaged = true;
                        damageClock.restart();
                    }
                }
            }

            if (hero.isAttacking() && hero.getSprite().getGlobalBounds().intersects(crab.getSprite().getGlobalBounds())) {
                crab.takeDamage(1);
            }

            if (!heart1.isCollected() && heart1.getSprite().getGlobalBounds().intersects(hero.getSprite().getGlobalBounds()) && hero.getHealth() < 3) {
                heart1.collect();
                hero.addHealth(window);
            }
        }

        if (currentMap == 1 || currentMap == 3) {
            for (const auto& spike : spikes) {
                if (spike.getGlobalBounds().intersects(hero.getSprite().getGlobalBounds())) {
                    hero.kill();
                    hero.setPosition(100, 0);
                    hero.resetHealth();
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
                    hero.takeDamage();
                    heroDamaged = true;
                    lastDamageTime = currentTime;
                    recentlyDamaged = true;
                    damageClock.restart();
                }
            }

            if (guy2.getisAttacking() && guy2.getSprite().getGlobalBounds().intersects(hero.getSprite().getGlobalBounds())) {
                if (!recentlyDamaged || (currentTime - lastDamageTime > sf::seconds(1.0f))) {
                    hero.takeDamage();
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
            pirate.update(platforms[1], hero.getSprite());
            handleCollisions(pirate, platforms);
            if (pirate.getisAttacking() && pirate.getSprite().getGlobalBounds().intersects(hero.getSprite().getGlobalBounds())) {
                hero.takeDamage();
                heroDamaged = true;
                lastDamageTime = currentTime;
                recentlyDamaged = true;
                damageClock.restart();
            }

            captain.update(platforms[5], hero.getSprite(), deltaTime);
            handleCollisions(captain, platforms);

            if (captain.getisAttacking() && captain.getSprite().getGlobalBounds().intersects(hero.getSprite().getGlobalBounds())) {
                if (!recentlyDamaged || (currentTime - lastDamageTime > sf::seconds(1.0f))) {
                    hero.takeDamage();
                    heroDamaged = true;
                    lastDamageTime = currentTime;
                    recentlyDamaged = true;
                    damageClock.restart();
                }
            }

            if (hero.isAttacking() && hero.getSprite().getGlobalBounds().intersects(captain.getSprite().getGlobalBounds())) {
                if (!recentlyinflictedDamage) {
                    captain.takeDamage(1);
                    lastInflictedDamageTime = currentTime2;
                    recentlyinflictedDamage = true;
                    damageClock2.restart();
                }
            }

            if (!heart2.isCollected() && heart2.getSprite().getGlobalBounds().intersects(hero.getSprite().getGlobalBounds()) && hero.getHealth() < 3) {
                heart2.collect();
                hero.addHealth(window);
            }
        }

        for (const auto& cannonball : cannon.getCannonballs()) {
            if (cannonball.getGlobalBounds().intersects(hero.getSprite().getGlobalBounds())) {
                if (recentlyDamaged && (clock.getElapsedTime().asSeconds() - lastDamageTime.asSeconds() > 0.5)) {
                    recentlyDamaged = false;
                }
                if (!recentlyDamaged) {
                    hero.takeDamage();
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
            hero.setPosition(100, 0);
            hero.resetHealth();
            hero.setHasKey(false);
            key.resetAnimation(1654, 440);
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
            keySprite.setPosition(160, 15);
            window.draw(keySprite);
        }

        window.draw(hero.getSprite());
        hero.draw(window);

        if (currentMap == 1) {
            if (crab.isCrabAlive()) { 
                window.draw(crab.getSprite()); }
            window.draw(floor);
            window.draw(cannon.getSprite());
            if (!heart1.isCollected()) {
                heart1.update(deltaTime);
                window.draw(heart1.getSprite());
            }
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
            if (captain.isAlive() || captain.getDeathElapsedTime() < sf::seconds(1.0f)) {
                window.draw(captain.getSprite());
            }
            if (!heart2.isCollected()) {
                heart2.update(deltaTime);
                window.draw(heart2.getSprite());
            }
        }

        window.display();
    }

    return 0;
}