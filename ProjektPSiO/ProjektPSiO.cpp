#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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
#include "Menu.h"
#include "Chest.h"
#include "DeathMenu.h"
#include "winMenu.h"


int main() {
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Projekt", sf::Style::Titlebar | sf::Style::Close);

    const float gravity = 0.0035f;
    int groundHeight = window.getSize().y - 200;
    int currentGroundHeight = groundHeight;

    bool iswon = false;
    bool isherodead = false;
    bool isMenuOpen = false; 
    Menu menu(window.getSize().x, window.getSize().y); 
    DeathMenu deathMenu(window.getSize().x, window.getSize().y);
    WinMenu WinMenu(window.getSize().x, window.getSize().y);

    std::vector <sf::Texture> idle(5);
    for (int i = 0; i < 5; i++) {
        if (!idle[i].loadFromFile("Hero/idle" + std::to_string(i + 1) + ".png")) {
            std::cerr << "Error loading idle texture " << i + 1 << std::endl;
            return -1;
        }
    }

    std::vector <sf::Texture> run(6);
    for (int i = 0; i < 6; i++) {
        if (!run[i].loadFromFile("Hero/run" + std::to_string(i + 1) + ".png")) {
            std::cerr << "Error loading run texture " << i + 1 << std::endl;
            return -1;
        }
    }

    sf::Texture jump;
    jump.loadFromFile("Hero/jump.png");

    std::vector <sf::Texture> attack(3);
    for (int i = 0; i < 3; i++) {
        if (!attack[i].loadFromFile("Hero/attack" + std::to_string(i + 1) + ".png")) {
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

    sf::Texture backgroundTexture1;
    sf::Texture backgroundTexture2;
    sf::Texture backgroundTexture3;

    if (!backgroundTexture1.loadFromFile("Map/background1.png")) {
        std::cerr << "Error loading background1.png" << std::endl;
        return -1;
    }

    if (!backgroundTexture2.loadFromFile("Map/background2.png")) {
        std::cerr << "Error loading background2.png" << std::endl;
        return -1;
    }

    if (!backgroundTexture3.loadFromFile("Map/background3tile.png")) {
        std::cerr << "Error loading background3tile.png" << std::endl;
        return -1;
    }
    backgroundTexture3.setRepeated(true);


    sf::Sprite backgroundsprite1;
    backgroundsprite1.setTexture(backgroundTexture1);
    sf::Sprite backgroundsprite2;
    backgroundsprite2.setTexture(backgroundTexture2);
    sf::Sprite backgroundsprite3;
    backgroundsprite3.setTexture(backgroundTexture3);
    backgroundsprite3.setScale(2.0f, 2.0f);


    std::vector <sf::Texture> level1textures(6);
    for (int i = 0; i < 6; i++) {
        if (!level1textures[i].loadFromFile("Map/level1" + std::to_string(i + 1) + ".png")) {
            std::cerr << "Error loading level1 texture" << std::endl;
        }
    }

    std::vector <sf::Texture> level2textures(5);
    for (int i = 0; i < 5; i++) {
        if (!level2textures[i].loadFromFile("Map/level2" + std::to_string(i + 1) + ".png")) {
            std::cerr << "Error loading level2 texture" << std::endl;
        }
    }

    std::vector <sf::Texture> level3textures(6);
    for (int i = 0; i < 6; i++) {
        if (!level3textures[i].loadFromFile("Map/level3" + std::to_string(i + 1) + ".png")) {
            std::cerr << "Error loading level3 texture" << std::endl;
        }
    }

    sf::Texture groundTexture;
    if (!groundTexture.loadFromFile("Map/ground.png")) {
        std::cerr << "Error loading ground texture" << std::endl;
        return -1;
    }

    sf::Texture ground3Texture;
    if (!ground3Texture.loadFromFile("Map/ground3.png")) {
        std::cerr << "Error loading ground3 texture" << std::endl;
        return -1;
    }

    sf::RectangleShape floor1(sf::Vector2f(window.getSize().x, 200));
    floor1.setTexture(&groundTexture);
    floor1.setPosition(0, groundHeight);

    sf::RectangleShape floor3(sf::Vector2f(window.getSize().x, 200));
    floor3.setTexture(&ground3Texture);
    floor3.setPosition(0, groundHeight);


    sf::Texture spikeTexture;
    if (!spikeTexture.loadFromFile("Map/Spikes.png")) {
        std::cerr << "Error loading spike texture" << std::endl;
        return -1;
    }

    //skrzynia
    sf::Texture closedChestTexture;
    closedChestTexture.loadFromFile("Chest/chestclosed.png");
    std::vector<sf::Texture> openChestTextures(8);
    for (int i = 0; i < 8; ++i) {
        if (!openChestTextures[i].loadFromFile("Chest/chestunlocked" + std::to_string(i + 1) + ".png")) {
            std::cerr << "Error loading chest texture" << std::endl;
            return -1;
        }
    }

    Chest chest(closedChestTexture, openChestTextures, 1650, 0);
    int chesty = groundHeight - chest.getSprite().getGlobalBounds().height;
    chest.getSprite().setPosition(1650, chesty);

    //armata
    sf::Texture cannonballTexture;
    if (!cannonballTexture.loadFromFile("Cannon/cball.png")) {
        std::cerr << "Error loading cannonball texture" << std::endl;
        return -1;
    }

    Cannon cannon(gravity, cannonballTexture);
    cannon.setPosition(650, groundHeight - cannon.getGlobalBounds().height);


    std::vector <sf::Texture> cshoot(6);
    for (int i = 0; i < 6; i++) {
        if (!cshoot[i].loadFromFile("Cannon/cshoot" + std::to_string(i + 1) + ".png")) {
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
        if (!crabRun[i].loadFromFile("Crab/crabrun" + std::to_string(i + 1) + ".png")) {
            std::cerr << "Error loading crab run texture " << i + 1 << std::endl;
            return -1;
        }
    }

    std::vector <sf::Texture> crabAttack(4);
    for (int i = 0; i < 4; i++) {
        if (!crabAttack[i].loadFromFile("Crab/crabattack" + std::to_string(i + 1) + ".png")) {
            std::cerr << "Error loading crab run texture " << i + 1 << std::endl;
            return -1;
        }
    }

    std::vector <sf::Texture> crabAnticipation(3);
    for (int i = 0; i < 3; i++) {
        if (!crabAnticipation[i].loadFromFile("Crab/crabanticipation" + std::to_string(i + 1) + ".png")) {
            std::cerr << "Error loading crab anticipation texture " << i + 1 << std::endl;
            return -1;
        }
    }

    sf::Texture crabHit;
    if (!crabHit.loadFromFile("Crab/crabhit.png")) {
        std::cerr << "Error loading crab hit texture " << std::endl;
        return -1;
    }

    sf::Texture crabDie;
    if (!crabDie.loadFromFile("Crab/crabdie.png")) {
        std::cerr << "Error loading crab die texture " << std::endl;
        return -1;
    }


    Crab crab(crabRun, crabAnticipation, crabAttack, crabHit, crabDie, gravity, 0.1f);
    crab.setPosition(1050, 329);

    //big guy
    std::vector<sf::Texture> bigguyidle(36);
    std::vector<sf::Texture> bigguyrun(8);
    std::vector<sf::Texture> bigguyattack(10);
    for (int i = 0; i < 36; ++i) {
        if (!bigguyidle[i].loadFromFile("Big Guy/guyidle" + std::to_string(i + 1) + ".png")) {
            std::cerr << "Error loading idle texture " << i + 1 << std::endl;
            return -1;
        }
    }

    for (int i = 0; i < 8; ++i) {
        if (!bigguyrun[i].loadFromFile("Big Guy/guyrun" + std::to_string(i + 1) + ".png")) {
            std::cerr << "Error loading run texture " << i + 1 << std::endl;
            return -1;
        }
    }

    for (int i = 0; i < 10; ++i) {
        if (!bigguyattack[i].loadFromFile("Big Guy/bigguyattack" + std::to_string(i + 1) + ".png")) {
            std::cerr << "Error loading attack texture " << i + 1 << std::endl;
            return -1;
        }
    }

    sf::Texture bigguyHit;
    if (!bigguyHit.loadFromFile("Big Guy/bigguyhit.png")) {
        std::cerr << "Error loading big guy hit texture " << std::endl;
        return -1;
    }

    sf::Texture bigguyDie;
    if (!bigguyDie.loadFromFile("Big Guy/bigguydie.png")) {
        std::cerr << "Error loading big guy die texture " << std::endl;
        return -1;
    }

    BigGuy guy1(bigguyidle, bigguyrun, bigguyattack, bigguyHit, bigguyDie, gravity, 0.2f);
    BigGuy guy2(bigguyidle, bigguyrun, bigguyattack, bigguyHit, bigguyDie, gravity, 0.2f);
    guy1.setPosition(1002, 250 - guy1.getSprite().getGlobalBounds().height);
    guy2.setPosition(1502, groundHeight - 396 - guy2.getSprite().getGlobalBounds().height);


    //pirat
    std::vector <sf::Texture> pirateattack(12);
    for (int i = 0; i < 12; ++i) {
        if (!pirateattack[i].loadFromFile("Pirate/pirateattack" + std::to_string(i + 1) + ".png")) {
            std::cerr << "Error loading pirate attack texture " << i + 1 << std::endl;
            return -1;
        }
    }
    std::vector <sf::Texture> pirateidle(34);
    for (int i = 0; i < 34; ++i) {
        if (!pirateidle[i].loadFromFile("Pirate/pirateidle" + std::to_string(i + 1) + ".png")) {
            std::cerr << "Error loading pirateidle texture " << i + 1 << std::endl;
            return -1;
        }
    }

    std::vector <sf::Texture> piraterun(14);
    for (int i = 0; i < 14; ++i) {
        if (!piraterun[i].loadFromFile("Pirate/piraterun" + std::to_string(i + 1) + ".png")) {
            std::cerr << "Error loading piraterun texture " << i + 1 << std::endl;
            return -1;
        }
    }

    sf::Texture piratehit;
    if (!piratehit.loadFromFile("Pirate/piratehit.png")) {
        std::cerr << "Error loading piratehit texture " << std::endl;
        return -1;
    }
    sf::Texture piratedie;
    if (!piratedie.loadFromFile("Pirate/piratedie.png")) {
        std::cerr << "Error loading piratediedie texture " << std::endl;
        return -1;
    }

    Pirate pirate(pirateidle, piraterun, pirateattack, piratehit, piratedie, gravity, 0.5f);
    pirate.setPosition(1000, 150 - pirate.getSprite().getGlobalBounds().height);

    //kapitan
    std::vector <sf::Texture> captainrun(14);
    for (int i = 0; i < 14; ++i) {
        if (!captainrun[i].loadFromFile("Captain/captainrun" + std::to_string(i + 1) + ".png")) {
            std::cerr << "Error loading captainrun texture " << i + 1 << std::endl;
            return -1;
        }
    }

    std::vector <sf::Texture> captainattack(7);
    for (int i = 0; i < 7; ++i) {
        if (!captainattack[i].loadFromFile("Captain/captainattack" + std::to_string(i + 1) + ".png")) {
            std::cerr << "Error loading captainattack texture " << i + 1 << std::endl;
            return -1;
        }
    }

    sf::Texture captainhit;
    if (!captainhit.loadFromFile("Captain/captainhit.png")) {
        std::cerr << "Error loading captainhit texture " << std::endl;
        return -1;
    }
    sf::Texture captaindie;
    if (!captaindie.loadFromFile("Captain/captaindie.png")) {
        std::cerr << "Error loading captaindie texture " << std::endl;
        return -1;
    }


    Captain captain(captainrun, captainattack, captainhit, captaindie, gravity, 0.1f);
    captain.setPosition(800, groundHeight - 280 - captain.getSprite().getGlobalBounds().height);

    std::vector<sf::Texture> keyTextures(8);
    for (int i = 0; i < 8; ++i) {
        if (!keyTextures[i].loadFromFile("Items/key" + std::to_string(i + 1) + ".png")) {
            std::cerr << "Error loading key texture " << i + 1 << std::endl;
            return -1;
        }
    }

    Collectable key(keyTextures, 1654, 440);


    std::vector <sf::Texture> heartTextures(22);
    for (int i = 0; i < 22; ++i) {
        if (!heartTextures[i].loadFromFile("Items/heart" + std::to_string(i + 1) + ".png")) {
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
    loadMap(currentMap, platforms, backgroundElements, spikes, groundHeight, spikeTexture, level1textures, level2textures, level3textures);


    sf::Music backgroundMusic;
    if (!backgroundMusic.openFromFile("backgroundmusic.wav")) {
        std::cerr << "Error loading music" << std::endl;
        return -1;
    }
    backgroundMusic.setLoop(true);
    backgroundMusic.play();
    float volume = 10.0f;
    backgroundMusic.setVolume(volume);

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
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                isMenuOpen = !isMenuOpen;
            }
            if (chest.isOpened()) {
                iswon = true;
            }
            if (isMenuOpen) {
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                        for (int i = 0; i < menu.getNumberOfItems(); i++) {
                            if (menu.isMouseOver(mousePos, i)) {
                                if (i == 0) {                                    
                                    isMenuOpen = false;
                                }
                                else if (i == 1) {                                    
                                    window.close();
                                }
                                else if (i == 2) {
                               
                                    resetGame(hero, crab, guy1, guy2, pirate, captain, key, heart1, heart2, platforms, spikes, backgroundElements, currentMap, groundHeight, spikeTexture,level1textures,level2textures, level3textures, chest);
                                    isMenuOpen = false;
                                }
                            }
                        }
                    }
                }
            }
            if (isherodead) {
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                        int buttonIndex = deathMenu.handleMouseClick(mousePos);
                        if (buttonIndex == 0) {
                            // Reset Game
                            resetGame(hero, crab, guy1, guy2, pirate, captain, key, heart1, heart2, platforms, spikes, backgroundElements, currentMap, groundHeight, spikeTexture, level1textures, level2textures, level3textures,  chest);
                            isherodead = false;
                        }
                        else if (buttonIndex == 1) {
                            // Quit
                            window.close();
                        }
                    }
                }
            }
            if (iswon) {
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                        int buttonIndex = WinMenu.handleMouseClick(mousePos);
                        if (buttonIndex == 0) {
                            // Reset Game
                            resetGame(hero, crab, guy1, guy2, pirate, captain, key, heart1, heart2, platforms, spikes, backgroundElements, currentMap, groundHeight, spikeTexture, level1textures, level2textures, level3textures, chest);
                            iswon = false;
                        }
                        else if (buttonIndex == 1) {
                            // Quit
                            window.close();
                        }
                    }
                }
            }
        }

        if (!isMenuOpen) {
            if (!isherodead) {
                if (!iswon) {
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
                        if (crab.isAlive()) {
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
                            if (!recentlyinflictedDamage) {
                                crab.takeDamage(1);
                                lastInflictedDamageTime = currentTime2;
                                recentlyinflictedDamage = true;
                                damageClock2.restart();
                            }
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

                            }
                        }
                    }


                    if (currentMap == 2) {
                        guy1.update(platforms[3], hero.getSprite(), deltaTime);
                        guy2.update(platforms[1], hero.getSprite(), deltaTime);
                        key.update(deltaTime);

                        handleCollisions(guy1, platforms);
                        handleCollisions(guy2, platforms);

                        if (guy1.getIsAttacking() && guy1.getSprite().getGlobalBounds().intersects(hero.getSprite().getGlobalBounds())) {
                            if (isHeroInFront(guy1.getSprite(), hero.getSprite())) {
                                if (!recentlyDamaged || (currentTime - lastDamageTime > sf::seconds(1.0f))) {
                                    hero.takeDamage();
                                    heroDamaged = true;
                                    lastDamageTime = currentTime;
                                    recentlyDamaged = true;
                                    damageClock.restart();
                                }
                            }
                        }

                        if (hero.isAttacking() && hero.getSprite().getGlobalBounds().intersects(guy1.getSprite().getGlobalBounds())) {
                            if (!recentlyinflictedDamage) {
                                guy1.takeDamage(1);
                                lastInflictedDamageTime = currentTime2;
                                recentlyinflictedDamage = true;
                                damageClock2.restart();
                            }
                        }

                        if (guy2.getIsAttacking() && guy2.getSprite().getGlobalBounds().intersects(hero.getSprite().getGlobalBounds())) {
                            if (isHeroInFront(guy2.getSprite(), hero.getSprite())) {
                                if (!recentlyDamaged || (currentTime - lastDamageTime > sf::seconds(1.0f))) {
                                    hero.takeDamage();
                                    heroDamaged = true;
                                    lastDamageTime = currentTime;
                                    recentlyDamaged = true;
                                    damageClock.restart();
                                }
                            }
                        }

                        if (hero.isAttacking() && hero.getSprite().getGlobalBounds().intersects(guy2.getSprite().getGlobalBounds())) {
                            if (!recentlyinflictedDamage) {
                                guy2.takeDamage(1);
                                lastInflictedDamageTime = currentTime2;
                                recentlyinflictedDamage = true;
                                damageClock2.restart();
                            }
                        }

                        if (!key.isCollected() && key.getSprite().getGlobalBounds().intersects(hero.getSprite().getGlobalBounds())) {
                            key.collect();
                            hero.pickUpKey();
                        }

                        if (hero.getPosition().y > window.getSize().y) {
                            hero.kill();
                        }
                    }

                    if (currentMap == 3) {
                        pirate.update(platforms[5], hero.getSprite(), deltaTime);
                        handleCollisions(pirate, platforms);

                        if (pirate.getIsAttacking() && pirate.getSprite().getGlobalBounds().intersects(hero.getSprite().getGlobalBounds())) {
                            if (isHeroInFront(pirate.getSprite(), hero.getSprite())) {
                                if (!recentlyDamaged || (currentTime - lastDamageTime > sf::seconds(1.0f))) {
                                    hero.takeDamage();
                                    heroDamaged = true;
                                    lastDamageTime = currentTime;
                                    recentlyDamaged = true;
                                    damageClock.restart();
                                }
                            }
                        }

                        if (hero.isAttacking() && hero.getSprite().getGlobalBounds().intersects(pirate.getSprite().getGlobalBounds())) {
                            if (!recentlyinflictedDamage) {
                                pirate.takeDamage(1);
                                lastInflictedDamageTime = currentTime2;
                                recentlyinflictedDamage = true;
                                damageClock2.restart();
                            }
                        }

                        captain.update(platforms[5], hero.getSprite(), deltaTime);
                        handleCollisions(captain, platforms);

                        if (captain.getIsAttacking() && captain.getSprite().getGlobalBounds().intersects(hero.getSprite().getGlobalBounds())) {
                            if (isHeroInFront(captain.getSprite(), hero.getSprite())) {
                                if (!recentlyDamaged || (currentTime - lastDamageTime > sf::seconds(1.0f))) {
                                    hero.takeDamage();
                                    heroDamaged = true;
                                    lastDamageTime = currentTime;
                                    recentlyDamaged = true;
                                    damageClock.restart();
                                }
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

                        chest.update(deltaTime);
                        if (hero.getHasKey() && hero.getSprite().getGlobalBounds().intersects(chest.getSprite().getGlobalBounds())) {
                            chest.open();
                            hero.dropKey();                            

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

                    if (!hero.isAlive()) {
                        isherodead = true;
                        hero.setHasKey(false);
                        key.resetAnimation(1654, 440);
                    }


                    if (hero.getPosition().x > window.getSize().x && currentMap == 1) {
                        currentMap++;
                        loadMap(currentMap, platforms, spikes, backgroundElements, groundHeight, spikeTexture, level1textures, level2textures, level3textures);
                        hero.setPosition(0, hero.getPosition().y);
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && currentMap == 2 && hero.getPosition().x > 1024 && hero.getPosition().x < 1204) {
                        currentMap = 3;
                        loadMap(currentMap, platforms, spikes, backgroundElements, groundHeight, spikeTexture, level1textures, level2textures, level3textures);
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

                    //okno - rysowanie
                    window.clear(sf::Color(0, 240, 255));
                    sf::Vector2u windowSize = window.getSize();

                    if (currentMap == 1) {
                        sf::Vector2u textureSize = backgroundsprite1.getTexture()->getSize();
                        backgroundsprite1.setScale(
                            static_cast<float>(windowSize.x) / textureSize.x,
                            static_cast<float>(windowSize.y) / textureSize.y
                        );
                        window.draw(backgroundsprite1);
                    }
                    else if (currentMap == 2) {
                        sf::Vector2u textureSize = backgroundsprite2.getTexture()->getSize();
                        backgroundsprite2.setScale(
                            static_cast<float>(windowSize.x) / textureSize.x,
                            static_cast<float>(windowSize.y) / textureSize.y
                        );
                        window.draw(backgroundsprite2);
                    }
                    else if (currentMap == 3) {
                        backgroundsprite3.setTextureRect(sf::IntRect(0, 0, window.getSize().x, window.getSize().y));
                        window.draw(backgroundsprite3);

                    }

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

                    if (currentMap == 3) {
                        window.draw(chest.getSprite());
                    }
                    window.draw(hero.getSprite());
                    hero.draw(window);

                    if (currentMap == 1) {
                        if (crab.isAlive() || crab.getDeathElapsedTime() < sf::seconds(1.0f)) {
                            window.draw(crab.getSprite());
                        }
                        window.draw(floor1);
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

                        if (guy1.isAlive() || guy1.getDeathElapsedTime() < sf::seconds(1.0f)) {
                            window.draw(guy1.getSprite());
                        }
                        if (guy2.isAlive() || guy2.getDeathElapsedTime() < sf::seconds(1.0f)) {
                            window.draw(guy2.getSprite());
                        }
                        if (!key.isCollected()) {
                            key.update(deltaTime);
                            window.draw(key.getSprite());
                        }
                    }

                    if (currentMap == 3) {

                        window.draw(floor3);
                        if (pirate.isAlive() || pirate.getDeathElapsedTime() < sf::seconds(1.0f)) {
                            window.draw(pirate.getSprite());
                        }
                        if (captain.isAlive() || captain.getDeathElapsedTime() < sf::seconds(1.0f)) {
                            window.draw(captain.getSprite());
                        }
                        if (!heart2.isCollected()) {
                            heart2.update(deltaTime);
                            window.draw(heart2.getSprite());
                        }
                    }
                }
            }
        }
        if (iswon) {            
            WinMenu.draw(window);
        }
        if (isherodead) {
            deathMenu.draw(window);
        }

        if (isMenuOpen) {
            menu.draw(window); 
        }

        window.display(); 
    }

    return 0;


}