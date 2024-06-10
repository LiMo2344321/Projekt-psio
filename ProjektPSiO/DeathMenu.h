#ifndef DEATHMENU_H
#define DEATHMENU_H

#include <SFML/Graphics.hpp>
#include <vector>

class DeathMenu {
public:
    DeathMenu(float width, float height);
    void draw(sf::RenderWindow& window);
    bool isMouseOver(const sf::Vector2i& mousePos, int index) const;
    int getSelectedItemIndex();
    void moveUp();
    void moveDown();
    int getNumberOfItems() const;
    int handleMouseClick(const sf::Vector2i& mousePos);

private:
    int selectedItemIndex;
    sf::Font font;
    sf::Texture menuBackgroundTexture;
    sf::Sprite menuBackground;
    sf::Texture buttonTexture;
    sf::Texture youDiedTexture;
    sf::Texture restartTexture;
    sf::Texture quitTexture;
    sf::Sprite youDiedSprite;
    sf::Sprite restartTextSprite;
    sf::Sprite quitTextSprite;
    std::vector<sf::Sprite> buttons;
};

#endif // DEATHMENU_H
