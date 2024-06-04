#include "Map.h"

void loadMap(int mapIndex, std::vector<sf::RectangleShape>& platforms, std::vector<sf::Sprite>& backgroundElements, int groundHeight, sf::Texture& shipTexture, sf::Texture& mastTexture, sf::Texture& flagTexture) {
    platforms.clear();
    backgroundElements.clear();

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
    }
    else if (mapIndex == 2) {
        //level2
        // port
        sf::RectangleShape platform1(sf::Vector2f(180, 200));
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
    }
}