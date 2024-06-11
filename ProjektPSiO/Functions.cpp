#include "Functions.h"
#include "Hero.h"
#include "Cannon.h"
#include "Crab.h"
#include "BigGuy.h"
#include "Pirate.h"
#include "Captain.h"
#include "Collectable.h"
#include "Chest.h"

void loadMap(int mapIndex, std::vector<sf::RectangleShape>& platforms, std::vector<sf::Sprite>& backgroundElements, std::vector<sf::Sprite>& spikes, int groundHeight, sf::Texture& spikeTexture, std::vector <sf::Texture>& level1textures, std::vector <sf::Texture>& level2textures, std::vector <sf::Texture>& level3textures) {
    platforms.clear();
    backgroundElements.clear();
    spikes.clear();

    if (mapIndex == 1) {
        //level1
        sf::RectangleShape platform1(sf::Vector2f(200, 150));
        platform1.setTexture(&level1textures[0]);
        platform1.setPosition(200, groundHeight - 150);
        platforms.push_back(platform1);

        sf::RectangleShape platform2(sf::Vector2f(180, 250));
        platform2.setTexture(&level1textures[1]);
        platform2.setPosition(750, groundHeight - 250);
        platforms.push_back(platform2);

        sf::RectangleShape platform3(sf::Vector2f(300, 50));
        platform3.setTexture(&level1textures[2]);
        platform3.setPosition(1100, 400);
        platforms.push_back(platform3);

        sf::RectangleShape platform4(sf::Vector2f(300, 50));
        platform4.setTexture(&level1textures[3]);
        platform4.setPosition(1400, 700);
        platforms.push_back(platform4);

        sf::RectangleShape platform5(sf::Vector2f(100, 50));
        platform5.setTexture(&level1textures[4]);
        platform5.setPosition(900, 200);
        platforms.push_back(platform5);

        //port
        sf::RectangleShape platform6(sf::Vector2f(180, 200));
        platform6.setTexture(&level1textures[5]);
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
        platform1.setTexture(&level2textures[0]);
        platform1.setPosition(0, groundHeight - 200);
        platforms.push_back(platform1);

        // statek
        sf::RectangleShape platform2(sf::Vector2f(1404, 396));
        platform2.setTexture(&level2textures[1]);
        platform2.setPosition(350, groundHeight - 396);
        platforms.push_back(platform2);

        // maszt
        sf::RectangleShape platform3(sf::Vector2f(36, 450));
        platform3.setTexture(&level2textures[2]);
        platform3.setTextureRect(sf::IntRect(0, 0, 4, level2textures[2].getSize().y));
        platform3.setPosition(1052, groundHeight - 846);
        platforms.push_back(platform3);

        sf::RectangleShape platform4(sf::Vector2f(300, 50));
        platform4.setTexture(&level2textures[3]);
        platform4.setPosition(752, 250);
        platforms.push_back(platform4);

        // flaga 
        sf::Sprite flag;
        flag.setTexture(level2textures[4]);
        flag.setScale(9.0f, 9.0f);
        flag.setPosition(1088, groundHeight - 846);
        backgroundElements.push_back(flag);
    }
    else if (mapIndex == 3) {
        //level 3
        sf::RectangleShape platform1(sf::Vector2f(500, 50));
        platform1.setTexture(&level3textures[0]);
        platform1.setPosition(1600, 100);
        platforms.push_back(platform1);

        sf::RectangleShape platform2(sf::Vector2f(800, 50));
        platform2.setTexture(&level3textures[1]);
        platform2.setPosition(800, 150);
        platforms.push_back(platform2);

        sf::RectangleShape platform3(sf::Vector2f(500, 50));
        platform3.setTexture(&level3textures[2]);
        platform3.setPosition(300, 200);
        platforms.push_back(platform3);

        sf::RectangleShape platform4(sf::Vector2f(100, 50));
        platform4.setTexture(&level3textures[3]);
        platform4.setPosition(0, 400);
        platforms.push_back(platform4);

        sf::RectangleShape platform5(sf::Vector2f(300, 50));
        platform5.setTexture(&level3textures[4]);
        platform5.setPosition(300, 600);
        platforms.push_back(platform5);

        sf::RectangleShape platform6(sf::Vector2f(500, 50));
        platform6.setTexture(&level3textures[5]);
        platform6.setPosition(800, 600);
        platforms.push_back(platform6);
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

void resetGame(Hero& hero, Crab& crab, BigGuy& guy1, BigGuy& guy2, Pirate& pirate, Captain& captain, Collectable& key, Collectable& heart1, Collectable& heart2, std::vector<sf::RectangleShape>& platforms, std::vector<sf::Sprite>& spikes, std::vector<sf::Sprite>& backgroundElements, int& currentMap, int groundHeight, sf::Texture& spikeTexture, std::vector <sf::Texture>& level1textures, std::vector <sf::Texture>& level2textures, std::vector <sf::Texture>& level3textures, Chest& chest) {
    currentMap = 1;
    
    hero.setPosition(100, groundHeight);
    hero.resetHealth();
    hero.setHasKey(false);
    
    crab.reset();
    guy1.reset();
    guy2.reset();
    pirate.reset();
    captain.reset();
    key.resetAnimation(1654, 440);
    heart1.resetAnimation(930, 155);
    heart2.resetAnimation(30, 355);
    
    loadMap(currentMap, platforms, backgroundElements, spikes, groundHeight, spikeTexture, level1textures, level2textures, level3textures);
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




 