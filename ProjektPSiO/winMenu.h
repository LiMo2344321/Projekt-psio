#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class WinMenu {
public:
    WinMenu(float width, float height);
    void draw(sf::RenderWindow& window);
    bool isMouseOver(const sf::Vector2i& mousePos, int index) const;
    int getSelectedItemIndex();
    void moveUp();
    void moveDown();
    int getNumberOfItems() const;
    int handleMouseClick(const sf::Vector2i& mousePos);

private:
    sf::Texture menuBackgroundTexture;
    sf::Sprite menuBackground;
    sf::Texture buttonTexture;
    sf::Texture youWonTexture;
    sf::Texture restartTexture;
    sf::Texture quitTexture;
    sf::Sprite youWonSprite;
    sf::Sprite restartTextSprite;
    sf::Sprite quitTextSprite;
    std::vector<sf::Sprite> buttons;
    int selectedItemIndex;
};
