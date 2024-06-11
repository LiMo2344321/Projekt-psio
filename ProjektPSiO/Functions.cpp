#include "Functions.h"
#include "Hero.h"
#include "Cannon.h"
#include "Crab.h"
#include "BigGuy.h"
#include "Pirate.h"
#include "Captain.h"
#include "Collectable.h"
#include "Chest.h"

void loadMap(int mapIndex, std::vector<sf::RectangleShape>& platforms, std::vector<sf::Sprite>& backgroundElements, std::vector<sf::Sprite>& spikes, int groundHeight,sf::Texture& shipTexture, sf::Texture& mastTexture, sf::Texture& flagTexture, sf::Texture& spikeTexture) {
    platforms.clear();
    backgroundElements.clear();
    spikes.clear();

    if (mapIndex == 1) {
        //level1
        sf::RectangleShape platform1(sf::Vector2f(200, 150));
        platform1.setFillColor(sf::Color::Red);
        platform1.setPosition(200, groundHeight - 150);
        platforms.push_back(platform1);

        sf::RectangleShape platform2(sf::Vector2f(180, 250));
        platform2.setFillColor(sf::Color::Red);
        platform2.setPosition(750, groundHeight - 250);
        platforms.push_back(platform2);

        sf::RectangleShape platform3(sf::Vector2f(300, 50));
        platform3.setFillColor(sf::Color::Red);
        platform3.setPosition(1100, 400);
        platforms.push_back(platform3);

        sf::RectangleShape platform4(sf::Vector2f(300, 50));
        platform4.setFillColor(sf::Color::Red);
        platform4.setPosition(1400, 700);
        platforms.push_back(platform4);

        sf::RectangleShape platform5(sf::Vector2f(100, 50));
        platform5.setFillColor(sf::Color::Red);
        platform5.setPosition(900, 200);
        platforms.push_back(platform5);

        //port
        sf::RectangleShape platform6(sf::Vector2f(180, 200));
        platform6.setFillColor(sf::Color::Red);
        platform6.setPosition(1800, groundHeight - 200);
        platforms.push_back(platform6);

        //kolce

        float spikeWidth = 32.0f;
        float spikeHeight = 16.0f;
        float targetHeight = 50.0f;  
        float scaleX = targetHeight / spikeHeight;
        float startX = 930; 
        float endX = 1800;  

        spikeTexture.setRepeated(true);

        sf::Sprite spikes1;
        spikes1.setTexture(spikeTexture);
        spikes1.setTextureRect(sf::IntRect(0, 0, (endX - startX) / scaleX, spikeHeight));  
        spikes1.setScale(scaleX, scaleX);
        spikes1.setPosition(startX, groundHeight - targetHeight);
        spikes.push_back(spikes1);


    }
    else if (mapIndex == 2) {
        //level2
        // port
        sf::RectangleShape platform1(sf::Vector2f(180, 400));
        platform1.setFillColor(sf::Color::Red);
        platform1.setPosition(0, groundHeight - 200);
        platforms.push_back(platform1);

        // statek
        sf::RectangleShape platform2(sf::Vector2f(1404, 396));
        platform2.setTexture(&shipTexture);
        platform2.setPosition(300, groundHeight - 396);
        platforms.push_back(platform2);

        // maszt
        sf::RectangleShape platform3(sf::Vector2f(36, 450));
        platform3.setTexture(&mastTexture);
        platform3.setTextureRect(sf::IntRect(0, 0, 4, mastTexture.getSize().y));
        platform3.setPosition(1002, groundHeight - 846);
        platforms.push_back(platform3);

        sf::RectangleShape platform4(sf::Vector2f(300, 50));
        platform4.setFillColor(sf::Color::Red);
        platform4.setPosition(702, 250);
        platforms.push_back(platform4);

        // flaga 
        sf::Sprite flag;
        flag.setTexture(flagTexture);
        flag.setScale(9.0f, 9.0f);
        flag.setPosition(1038, groundHeight - 846);
        backgroundElements.push_back(flag);
    }
    else if (mapIndex == 3) {
        //level 3
        sf::RectangleShape platform1(sf::Vector2f(500, 50));
        platform1.setFillColor(sf::Color::Red);
        platform1.setPosition(1600, 100);
        platforms.push_back(platform1);

        sf::RectangleShape platform2(sf::Vector2f(800, 50));
        platform2.setFillColor(sf::Color::Red);
        platform2.setPosition(800, 150);
        platforms.push_back(platform2);

        sf::RectangleShape platform3(sf::Vector2f(500, 50));
        platform3.setFillColor(sf::Color::Red);
        platform3.setPosition(300, 200);
        platforms.push_back(platform3);

        sf::RectangleShape platform4(sf::Vector2f(100, 50));
        platform4.setFillColor(sf::Color::Red);
        platform4.setPosition(0, 400);
        platforms.push_back(platform4);

        sf::RectangleShape platform5(sf::Vector2f(300, 50));
        platform5.setFillColor(sf::Color::Red);
        platform5.setPosition(300, 600);
        platforms.push_back(platform5);

        sf::RectangleShape platform6(sf::Vector2f(500, 50));
        platform6.setFillColor(sf::Color::Red);
        platform6.setPosition(800, 600);
        platforms.push_back(platform6);

        //kolce
        float spikeWidth = 32.0f;
        float spikeHeight = 16.0f;
        float targetHeight = 50.0f;  

        float scaleX = targetHeight / spikeHeight;
        float startX = 0;
        float endX = 950;

        spikeTexture.setRepeated(true);

        sf::Sprite spikes2;
        spikes2.setTexture(spikeTexture);
        spikes2.setTextureRect(sf::IntRect(0, 0, (endX - startX) / scaleX, spikeHeight));  
        spikes2.setScale(scaleX, scaleX);
        spikes2.setPosition(0, groundHeight - 50);
        spikes.push_back(spikes2);
        
    }
}


void handleCollisions(Postac& character, const std::vector<sf::RectangleShape>& platforms) {
    for (const auto& platform : platforms) {
        if (character.getGlobalBounds().intersects(platform.getGlobalBounds())) {
            float characterBottom = character.getPosition().y + character.getGlobalBounds().height;
            float platformTop = platform.getPosition().y;
            float platformBottom = platform.getPosition().y + platform.getSize().y;
            float characterTop = character.getPosition().y;
            float characterLeft = character.getPosition().x - character.getGlobalBounds().width / 2.0f;
            float characterRight = character.getPosition().x + character.getGlobalBounds().width / 2.0f;
            float platformLeft = platform.getPosition().x;
            float platformRight = platform.getPosition().x + platform.getSize().x;

            // Kolizja z góry platformy
            if (characterBottom > platformTop && characterBottom < platformTop + 10 && character.getVelocity().y > 0) {
                character.setPosition(character.getPosition().x, platformTop - character.getGlobalBounds().height);
                character.setVely(0.00);
            }
            // Kolizja z do³u platformy
            else if (characterTop < platformBottom && characterTop > platformBottom - 10 && character.getVelocity().y < 0) {
                character.setPosition(character.getPosition().x, platformBottom);
                character.setVely(0.00);
            }
            // Kolizja z lewej strony platformy
            else if (characterRight > platformLeft && characterLeft < platformLeft && character.getVelocity().x > 0) {
                character.setPosition(platformLeft - character.getGlobalBounds().width / 2.0f, character.getPosition().y);
                character.setVelx(0.00);
            }
            // Kolizja z prawej strony platformy
            else if (characterLeft < platformRight && characterRight > platformRight && character.getVelocity().x < 0) {
                character.setPosition(platformRight + character.getGlobalBounds().width / 2.0f, character.getPosition().y);
                character.setVelx(0.00);
            }
        }
    }
}

void resetGame(Hero& hero, Crab& crab, BigGuy& guy1, BigGuy& guy2, Pirate& pirate, Captain& captain, Collectable& key, Collectable& heart1, Collectable& heart2, std::vector<sf::RectangleShape>& platforms, std::vector<sf::Sprite>& spikes, std::vector<sf::Sprite>& backgroundElements, int& currentMap, int groundHeight, sf::Texture& shipTexture, sf::Texture& mastTexture, sf::Texture& flagTexture, sf::Texture& spikeTexture, Chest& chest) {
    // Ustawienie mapy na pocz¹tkow¹
    currentMap = 1;

    // Resetowanie stanu bohatera
    hero.setPosition(100, groundHeight);
    hero.resetHealth();
    hero.setHasKey(false);

    // Resetowanie stanu wrogów i przedmiotów
    crab.reset();
    guy1.reset();
    guy2.reset();
    pirate.reset();
    captain.reset();
    key.resetAnimation(1654, 440);
    heart1.resetAnimation(930, 155);
    heart2.resetAnimation(30, 355);

    // Za³adowanie pocz¹tkowej mapy
    loadMap(currentMap, platforms, backgroundElements, spikes, groundHeight, shipTexture, mastTexture, flagTexture, spikeTexture);
    chest.reset();
}

bool isHeroInFront(const sf::Sprite& enemy, const sf::Sprite& hero) {
    float enemyLeft = enemy.getGlobalBounds().left;
    float enemyWidth = enemy.getGlobalBounds().width;
    float enemyRight = enemyLeft + enemyWidth;

    float heroLeft = hero.getGlobalBounds().left;
    float heroRight = heroLeft + hero.getGlobalBounds().width;

    return (heroLeft >= enemyLeft && heroLeft <= enemyLeft + enemyWidth / 2) ||
        (heroRight >= enemyLeft && heroRight <= enemyLeft + enemyWidth / 2);
}




 