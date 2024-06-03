#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

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

    std::vector<sf::RectangleShape> platforms;

    //pierwsza platforma
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
            }
        }

        sprite.move(velocity.x, velocity.y);

        window.clear(sf::Color(0, 240, 255));
        window.draw(sprite);
        window.draw(floor); 
        for (const auto& platform : platforms) {
            window.draw(platform);
        }
        window.display();
    }

    return 0;
}