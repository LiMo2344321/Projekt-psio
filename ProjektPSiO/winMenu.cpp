#include "WinMenu.h"

WinMenu::WinMenu(float width, float height) {
    // Load menu background (optional)
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

    // Initialize buttons
    sf::Sprite restartButton(buttonTexture);
    sf::Sprite quitButton(buttonTexture);
    restartButton.setScale(8.0f, 8.0f);
    quitButton.setScale(8.0f, 8.0f);
    restartButton.setPosition(800, 440); // Adjust position as needed
    quitButton.setPosition(800, 560);    // Adjust position as needed

    buttons.push_back(restartButton);
    buttons.push_back(quitButton);

    // Load and set the "You Won" title texture
    if (!youWonTexture.loadFromFile("menu/youwon.png")) {
        // Handle error
    }
    youWonSprite.setTexture(youWonTexture);
    youWonSprite.setScale(8.0f, 8.0f); // Scale the title sprite
    youWonSprite.setPosition(700, 300); // Position at the top

    // Load and set the restart button text texture
    if (!restartTexture.loadFromFile("menu/restart.png")) {
        // Handle error
    }
    restartTextSprite.setTexture(restartTexture);
    restartTextSprite.setScale(4.0f, 4.0f); // Scale the restart text sprite
    restartTextSprite.setPosition(restartButton.getPosition().x + (restartButton.getGlobalBounds().width - restartTextSprite.getGlobalBounds().width) / 2,
        restartButton.getPosition().y + (restartButton.getGlobalBounds().height - restartTextSprite.getGlobalBounds().height) / 2.6);

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

void WinMenu::draw(sf::RenderWindow& window) {
    window.draw(menuBackground);
    window.draw(youWonSprite);
    for (size_t i = 0; i < buttons.size(); i++) {
        window.draw(buttons[i]);
    }
    window.draw(restartTextSprite);
    window.draw(quitTextSprite);
}

bool WinMenu::isMouseOver(const sf::Vector2i& mousePos, int index) const {
    if (index < 0 || index >= buttons.size()) {
        return false;
    }
    return buttons[index].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}

int WinMenu::getSelectedItemIndex() {
    return selectedItemIndex;
}

void WinMenu::moveUp() {
    if (selectedItemIndex - 1 >= 0) {
        selectedItemIndex--;
    }
}

void WinMenu::moveDown() {
    if (selectedItemIndex + 1 < buttons.size()) {
        selectedItemIndex++;
    }
}

int WinMenu::getNumberOfItems() const {
    return buttons.size();
}

int WinMenu::handleMouseClick(const sf::Vector2i& mousePos) {
    for (int i = 0; i < buttons.size(); i++) {
        if (isMouseOver(mousePos, i)) {
            return i;  // Return the index of the clicked button
        }
    }
    return -1;  // Return -1 if no button was clicked
}
