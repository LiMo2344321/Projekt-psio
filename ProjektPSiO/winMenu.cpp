#include "WinMenu.h"
#include <iostream>

WinMenu::WinMenu(float width, float height) {    
    if (!menuBackgroundTexture.loadFromFile("menu/menuboard.png")) {
        std::cout << "Error loading menuboard texture" << std::endl;
    }
    menuBackground.setTexture(menuBackgroundTexture);
    menuBackground.setScale(8.0f, 8.0f); 
    menuBackground.setPosition(width / 2 - menuBackground.getGlobalBounds().width / 2, height / 2 - menuBackground.getGlobalBounds().height / 2);

    if (!buttonTexture.loadFromFile("menu/bigbutton.png")) {
        std::cout << "Error loading bigbutton texture" << std::endl;
    }

    sf::Sprite restartButton(buttonTexture);
    sf::Sprite quitButton(buttonTexture);
    restartButton.setScale(8.0f, 8.0f);
    quitButton.setScale(8.0f, 8.0f);
    restartButton.setPosition(800, 440); 
    quitButton.setPosition(800, 560);    

    buttons.push_back(restartButton);
    buttons.push_back(quitButton);

    if (!youWonTexture.loadFromFile("menu/youwon.png")) {
        std::cout << "Error loading youwon texture" << std::endl;
    }
    youWonSprite.setTexture(youWonTexture);
    youWonSprite.setScale(8.0f, 8.0f); 
    youWonSprite.setPosition(700, 300); 
    
    if (!restartTexture.loadFromFile("menu/restart.png")) {
        std::cout << "Error loading menurestart texture" << std::endl;
    }
    restartTextSprite.setTexture(restartTexture);
    restartTextSprite.setScale(4.0f, 4.0f); 
    restartTextSprite.setPosition(restartButton.getPosition().x + (restartButton.getGlobalBounds().width - restartTextSprite.getGlobalBounds().width) / 2,
        restartButton.getPosition().y + (restartButton.getGlobalBounds().height - restartTextSprite.getGlobalBounds().height) / 2.6);

    if (!quitTexture.loadFromFile("menu/quit.png")) {
        std::cout << "Error loading menuquit texture" << std::endl;
    }
    quitTextSprite.setTexture(quitTexture);
    quitTextSprite.setScale(4.0f, 4.0f); 
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
            return i;
        }
    }
    return -1;
}
