#include "Menu.h"

Menu::Menu(float width, float height) {
    // Load menu background
    if (!menuBackgroundTexture.loadFromFile("menu/menuboard.png")) {
        // Handle error
    }
    menuBackground.setTexture(menuBackgroundTexture);
    menuBackground.setScale(8.0f, 8.0f); // Scale the menu background
    menuBackground.setPosition(width / 2 - menuBackground.getGlobalBounds().width / 2, height / 2 - menuBackground.getGlobalBounds().height / 2);

    // Load button textures
    if (!buttonTexture.loadFromFile("menu/bigbutton.png")) {
        // Handle error
    }
    if (!biggerButtonTexture.loadFromFile("menu/biggerbutton.png")) {
        // Handle error
    }

    // Initialize buttons
    sf::Sprite continueButton(biggerButtonTexture); // Use biggerButtonTexture for continue button
    sf::Sprite quitButton(buttonTexture);
    continueButton.setScale(8.0f, 8.0f); // Scale the buttons
    quitButton.setScale(8.0f, 8.0f);     // Scale the buttons
    continueButton.setPosition(745, 440);
    quitButton.setPosition(800, 600);

    buttons.push_back(continueButton);
    buttons.push_back(quitButton);

    // Load and set the title texture
    if (!menuTitleTexture.loadFromFile("menu/menu.png")) {
        // Handle error
    }
    menuTitleSprite.setTexture(menuTitleTexture);
    menuTitleSprite.setScale(8.0f, 8.0f); // Scale the title sprite
    menuTitleSprite.setPosition(800, 300); // Position at the top

    // Load and set the continue button text texture
    if (!continueTexture.loadFromFile("menu/continue.png")) {
        // Handle error
    }
    continueTextSprite.setTexture(continueTexture);
    continueTextSprite.setScale(4.0f, 4.0f); // Scale the continue text sprite
    continueTextSprite.setPosition(continueButton.getPosition().x + (continueButton.getGlobalBounds().width - continueTextSprite.getGlobalBounds().width) / 2,
        continueButton.getPosition().y + (continueButton.getGlobalBounds().height - continueTextSprite.getGlobalBounds().height) / 2.6);

    // Load and set the quit button text texture
    if (!quitTexture.loadFromFile("menu/quit.png")) {
        // Handle error
    }
    quitTextSprite.setTexture(quitTexture);
    quitTextSprite.setScale(4.0f, 4.0f); // Scale the quit text sprite
    quitTextSprite.setPosition(quitButton.getPosition().x + (quitButton.getGlobalBounds().width - quitTextSprite.getGlobalBounds().width) / 2,
        quitButton.getPosition().y + (quitButton.getGlobalBounds().height - quitTextSprite.getGlobalBounds().height) / 2.6);

    selectedItemIndex = 0;
}

void Menu::draw(sf::RenderWindow& window) {
    window.draw(menuBackground);
    window.draw(menuTitleSprite);
    for (size_t i = 0; i < buttons.size(); i++) {
        window.draw(buttons[i]);
    }
    window.draw(continueTextSprite);
    window.draw(quitTextSprite);
}

bool Menu::isMouseOver(const sf::Vector2i& mousePos, int index) const {
    if (index < 0 || index >= buttons.size()) {
        return false;
    }
    return buttons[index].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}

int Menu::getSelectedItemIndex() {
    return selectedItemIndex;
}

void Menu::moveUp() {
    if (selectedItemIndex - 1 >= 0) {
        selectedItemIndex--;
    }
}

void Menu::moveDown() {
    if (selectedItemIndex + 1 < buttons.size()) {
        selectedItemIndex++;
    }
}

int Menu::getNumberOfItems() const {
    return buttons.size();
}
