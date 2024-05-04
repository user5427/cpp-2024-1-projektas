//
// Created by topto on 2024-05-02.
//

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "Button.h"

struct Button::ButtonImpl {
    bool showButton = true;
    bool disableButton = false;
    bool pressed = false;
    bool highlighted = false;
    int x, y, width, height;
    sf::Texture inactiveTexture, highlightedTexture, activeTexture, pressedTexture;

    ButtonImpl(std::string inactive, std::string highlight, std::string active, std::string pressed, int x, int y) {
        this->x = x;
        this->y = y;
        inactiveTexture.loadFromFile(inactive);
        highlightedTexture.loadFromFile(highlight);
        activeTexture.loadFromFile(active);
        pressedTexture.loadFromFile(pressed);
    }

    ~ButtonImpl() {

    }

    void draw(sf::RenderWindow& window) {
        if (!showButton) {
            return;
        }

        sf::Sprite sprite;
        if (pressed){
            sprite.setTexture(pressedTexture);
        } else if (highlighted) {
            sprite.setTexture(highlightedTexture);
        } else if (!disableButton) {
            sprite.setTexture(activeTexture);
        } else {
            sprite.setTexture(inactiveTexture);
        }

        sprite.setPosition(x, y);
        window.draw(sprite);
    }

    void update(sf::RenderWindow& window) {
        // check if the mouse is over the button
        highlighted = isOverButton(window);
    }

    bool isOverButton(sf::RenderWindow& window) {
        if (showButton && !disableButton){
            float Mx = sf::Mouse::getPosition(window).x;
            float My = sf::Mouse::getPosition(window).y;

            width = inactiveTexture.getSize().x;
            height = inactiveTexture.getSize().y;
            return Mx > x && Mx < x + width && My > y && My < y + height;
        } else
            return false;
    }

    void handleEvents(sf::RenderWindow& window, sf::Event event) {
        if (event.type == sf::Event::MouseButtonReleased && highlighted) {
            pressed = true;
        }
    }

    bool isPressed() {
        return pressed;
    }

    void show(bool showButton) {
        this->showButton = showButton;
    }

    void reset() {
        pressed = false;
        highlighted = false;
    }

    void disable(bool disableButton) {
        this->disableButton = disableButton;
        reset();
    }

};

Button::Button(std::string inactive, std::string highlight, std::string active, std::string pressed, int x, int y) : ptr(new ButtonImpl(inactive, highlight, active, pressed, x, y)) {
}

Button::~Button() {
    delete ptr;
}

void Button::draw(sf::RenderWindow& window) {
    ptr->draw(window);
}

void Button::update(sf::RenderWindow& window) {
    ptr->update(window);
}

void Button::handleEvents(sf::RenderWindow& window, sf::Event event) {
    ptr->handleEvents(window, event);
}

bool Button::isPressed() {
    return ptr->isPressed();
}

void Button::show(bool showButton) {
    ptr->show(showButton);
}

void Button::reset() {
    ptr->reset();
}

void Button::disable(bool disableButton) {
    ptr->disable(disableButton);
}

