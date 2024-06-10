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
    if (!restartButtonTexture.loadFromFile("menu/biggerbutton.png")) { // Zmienione na bigbutton.png
        // Handle error
    }

    // Initialize buttons
    sf::Sprite continueButton(biggerButtonTexture); // Use biggerButtonTexture for continue button
    sf::Sprite quitButton(buttonTexture);
    sf::Sprite restartButton(restartButtonTexture); // Zmienione na restartButtonTexture
    continueButton.setScale(8.0f, 8.0f); // Scale the buttons
    quitButton.setScale(8.0f, 8.0f);     // Scale the buttons
    restartButton.setScale(8.0f, 8.0f);   // Skalowanie przycisku restartu
    continueButton.setPosition(745, 440);
    quitButton.setPosition(800, 680);
    restartButton.setPosition(745, 560); // Pozycja przycisku restartu

    buttons.push_back(continueButton);
    buttons.push_back(quitButton);
    buttons.push_back(restartButton); // Dodanie przycisku restartu

    // Load and set the title texture
    if (!menuTitleTexture.loadFromFile("Menu/menu.png")) {
        // Handle error
    }
    menuTitleSprite.setTexture(menuTitleTexture);
    menuTitleSprite.setScale(8.0f, 8.0f); // Scale the title sprite
    menuTitleSprite.setPosition(800, 300); // Position at the top

    // Load and set the continue button text texture
    if (!continueTexture.loadFromFile("Menu/continue.png")) {
        // Handle error
    }
    continueTextSprite.setTexture(continueTexture);
    continueTextSprite.setScale(4.0f, 4.0f); // Scale the continue text sprite
    continueTextSprite.setPosition(continueButton.getPosition().x + (continueButton.getGlobalBounds().width - continueTextSprite.getGlobalBounds().width) / 2,
        continueButton.getPosition().y + (continueButton.getGlobalBounds().height - continueTextSprite.getGlobalBounds().height) / 2.6);

    // Load and set the quit button text texture
    if (!quitTexture.loadFromFile("Menu/quit.png")) {
        // Handle error
    }
    quitTextSprite.setTexture(quitTexture);
    quitTextSprite.setScale(4.0f, 4.0f); // Scale the quit text sprite
    quitTextSprite.setPosition(quitButton.getPosition().x + (quitButton.getGlobalBounds().width - quitTextSprite.getGlobalBounds().width) / 2,
        quitButton.getPosition().y + (quitButton.getGlobalBounds().height - quitTextSprite.getGlobalBounds().height) / 2.6);

    // Load and set the restart button text texture
    if (!restartTextTexture.loadFromFile("Menu/restart.png")) { // Nowy texture dla napisu restart
        // Handle error
    }
    restartTextSprite.setTexture(restartTextTexture);
    restartTextSprite.setScale(4.0f, 4.0f); // Scale the restart text sprite
    restartTextSprite.setPosition(restartButton.getPosition().x + (restartButton.getGlobalBounds().width - restartTextSprite.getGlobalBounds().width) / 2,
        restartButton.getPosition().y + (restartButton.getGlobalBounds().height - restartTextSprite.getGlobalBounds().height) / 2.6);

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
    window.draw(restartTextSprite); // Narysuj tekst na przycisku restartu
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
