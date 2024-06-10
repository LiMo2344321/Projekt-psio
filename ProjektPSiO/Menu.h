#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <vector>

class Menu {
public:
    Menu(float width, float height);
    void draw(sf::RenderWindow& window);
    bool isMouseOver(const sf::Vector2i& mousePos, int index) const;
    int getSelectedItemIndex();
    void moveUp();
    void moveDown();
    int getNumberOfItems() const;

private:
    int selectedItemIndex;
    sf::Font font;
    sf::Texture menuBackgroundTexture;
    sf::Sprite menuBackground;
    sf::Texture buttonTexture;
    sf::Texture biggerButtonTexture;
    sf::Texture menuTitleTexture;
    sf::Texture continueTexture;
    sf::Texture quitTexture;
    sf::Sprite menuTitleSprite;
    sf::Sprite continueTextSprite;
    sf::Sprite quitTextSprite;
    std::vector<sf::Sprite> buttons;
};

#endif // MENU_H
