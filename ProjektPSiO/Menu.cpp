#include "Menu.h"
#include <iostream>

Menu::Menu(float width, float height) {
    if (!menuBackgroundTexture.loadFromFile("menu/menuboard.png")) {
        std::cout << "Error loading menuboard texture" << std::endl;
    }
    menuBackground.setTexture(menuBackgroundTexture);
    menuBackground.setScale(8.0f, 8.0f); 
    menuBackground.setPosition(width / 2 - menuBackground.getGlobalBounds().width / 2, height / 2 - menuBackground.getGlobalBounds().height / 2);
      
    if (!buttonTexture.loadFromFile("menu/bigbutton.png")) {
        std::cout << "Error loading bigbutton texture" << std::endl;
    }
    if (!biggerButtonTexture.loadFromFile("menu/biggerbutton.png")) {
        std::cout << "Error loading biggerbutton texture" << std::endl;
    }
    if (!restartButtonTexture.loadFromFile("menu/biggerbutton.png")) { 
        std::cout << "Error loading biggerbutton texture" << std::endl;
    }

    
    sf::Sprite continueButton(biggerButtonTexture); 
    sf::Sprite quitButton(buttonTexture);
    sf::Sprite restartButton(restartButtonTexture); 
    continueButton.setScale(8.0f, 8.0f); 
    quitButton.setScale(8.0f, 8.0f);     
    restartButton.setScale(8.0f, 8.0f);   
    continueButton.setPosition(745, 440);
    quitButton.setPosition(800, 680);
    restartButton.setPosition(745, 560); 

    buttons.push_back(continueButton);
    buttons.push_back(quitButton);
    buttons.push_back(restartButton); 

    
    if (!menuTitleTexture.loadFromFile("Menu/menu.png")) {
        std::cout << "Error loading menu texture" << std::endl;
    }
    menuTitleSprite.setTexture(menuTitleTexture);
    menuTitleSprite.setScale(8.0f, 8.0f); 
    menuTitleSprite.setPosition(800, 300); 

    
    if (!continueTexture.loadFromFile("Menu/continue.png")) {
        std::cout << "Error loading continue texture" << std::endl;
    }
    continueTextSprite.setTexture(continueTexture);
    continueTextSprite.setScale(4.0f, 4.0f); 
    continueTextSprite.setPosition(continueButton.getPosition().x + (continueButton.getGlobalBounds().width - continueTextSprite.getGlobalBounds().width) / 2,
        continueButton.getPosition().y + (continueButton.getGlobalBounds().height - continueTextSprite.getGlobalBounds().height) / 2.6);

    
    if (!quitTexture.loadFromFile("Menu/quit.png")) {
        std::cout << "Error loading quit texture" << std::endl;
    }
    quitTextSprite.setTexture(quitTexture);
    quitTextSprite.setScale(4.0f, 4.0f); 
    quitTextSprite.setPosition(quitButton.getPosition().x + (quitButton.getGlobalBounds().width - quitTextSprite.getGlobalBounds().width) / 2,
        quitButton.getPosition().y + (quitButton.getGlobalBounds().height - quitTextSprite.getGlobalBounds().height) / 2.6);
        
    if (!restartTextTexture.loadFromFile("Menu/restart.png")) { 
        std::cout << "Error loading restart texture" << std::endl;
    }
    restartTextSprite.setTexture(restartTextTexture);
    restartTextSprite.setScale(4.0f, 4.0f); 
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
    window.draw(restartTextSprite); 
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
