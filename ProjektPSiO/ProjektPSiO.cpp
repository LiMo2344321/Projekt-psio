#include<SFML/Graphics.hpp>
#include<iostream>

int main()
{
    sf::RenderWindow Window(sf::VideoMode(640, 480, 32), "Gravity");

    const float gravity = 0.001f;
    int groundHeight = 440;
    sf::Vector2f velocity(0, 0);

    // Load texture from file
    sf::Texture texture;
    if (!texture.loadFromFile("idle.png"))
    {
        std::cerr << "Error loading texture" << std::endl;
        return -1;
    }

    // Create sprite and set its texture
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(0, 0);

    // Create platforms
    sf::RectangleShape platform1(sf::Vector2f(100, 20));
    platform1.setFillColor(sf::Color::Red);
    platform1.setPosition(200, 300);

    sf::RectangleShape platform2(sf::Vector2f(100, 20));
    platform2.setFillColor(sf::Color::Red);
    platform2.setPosition(400, 200);

    float moveSpeed = 0.3f, jumpSpeed = 0.6f;

    while (Window.isOpen())
    {
        sf::Event Event;
        while (Window.pollEvent(Event))
        {
            switch (Event.type)
            {
            case sf::Event::Closed:
                Window.close();
                break;
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
                (sprite.getPosition().x + sprite.getGlobalBounds().width > platform1.getPosition().x &&
                    sprite.getPosition().x < platform1.getPosition().x + platform1.getSize().x &&
                    sprite.getPosition().y + sprite.getGlobalBounds().height == platform1.getPosition().y) ||
                (sprite.getPosition().x + sprite.getGlobalBounds().width > platform2.getPosition().x &&
                    sprite.getPosition().x < platform2.getPosition().x + platform2.getSize().x &&
                    sprite.getPosition().y + sprite.getGlobalBounds().height == platform2.getPosition().y)))
        {
            velocity.y = -jumpSpeed;
        }

        if (sprite.getPosition().y + sprite.getGlobalBounds().height < groundHeight || velocity.y < 0)
        {
            velocity.y += gravity;
        }
        else
        {
            sprite.setPosition(sprite.getPosition().x, groundHeight - sprite.getGlobalBounds().height);
            velocity.y = 0;
        }

        // Platform collision detection
        if (sprite.getGlobalBounds().intersects(platform1.getGlobalBounds()))
        {
            if (sprite.getPosition().y + sprite.getGlobalBounds().height - velocity.y <= platform1.getPosition().y)
            {
                sprite.setPosition(sprite.getPosition().x, platform1.getPosition().y - sprite.getGlobalBounds().height);
                velocity.y = 0;
            }
        }

        if (sprite.getGlobalBounds().intersects(platform2.getGlobalBounds()))
        {
            if (sprite.getPosition().y + sprite.getGlobalBounds().height - velocity.y <= platform2.getPosition().y)
            {
                sprite.setPosition(sprite.getPosition().x, platform2.getPosition().y - sprite.getGlobalBounds().height);
                velocity.y = 0;
            }
        }

        sprite.move(velocity.x, velocity.y);

        Window.clear(sf::Color(0, 240, 255));
        Window.draw(sprite);
        Window.draw(platform1);
        Window.draw(platform2);
        Window.display();
    }

    return 0;
}
