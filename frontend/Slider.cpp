//
// Created by topto on 2024-05-03.
//

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include "Slider.h"

struct Slider::SliderImpl {
    int x, y;
    bool vertical;
    float tempX, tempY;
    float maxX, maxY;
    bool active = false;
    bool showSlider = true;
    bool disableSlider = false;
    float value = 0;

    float mouseX, mouseY;
    float sliderX, sliderY;
    bool mousePressed = false;

    sf::Texture sliderActiveTexture, sliderInactiveTexture, sliderTexture;

    SliderImpl(int x, int y, float length, bool vertical) {
        this->x = x;
        this->y = y;
        this->vertical = vertical;
        this->tempX = x;
        this->tempY = y;
        if (vertical) {
            this->maxX = x;
            this->maxY = y + length;
        } else {
            this->maxX = x + length;
            this->maxY = y;
        }

        sliderActiveTexture.loadFromFile("res/sliderActive.png");
        sliderInactiveTexture.loadFromFile("res/sliderInactive.png");
        sliderTexture.loadFromFile("res/slider.png");
    }

    ~SliderImpl() {

    }

    void draw(sf::RenderWindow &window) {
        if (!showSlider) {
            return;
        }

        sf::Sprite slider;
        if (active) {
            slider.setTexture(sliderActiveTexture);
        } else if (disableSlider) {
            slider.setTexture(sliderInactiveTexture);
        } else {
            slider.setTexture(sliderTexture);
        }

        slider.setPosition(tempX, tempY);

        window.draw(slider);
    }

    bool isMouseOver(sf::RenderWindow &window) {
        if (showSlider && !disableSlider) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            return mousePos.x >= tempX && mousePos.x <= tempX + sliderActiveTexture.getSize().x &&
                   mousePos.y >= tempY && mousePos.y <= tempY + sliderActiveTexture.getSize().y;
        } else
            return false;
    }

    void update(sf::RenderWindow &window) {
        if (mousePressed) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (vertical) {
                tempY = sliderY + (mousePos.y - mouseY);
            } else {
                tempX = sliderX + (mousePos.x - mouseX);
            }

            if (tempX < x) {
                tempX = x;
            } else if (tempX > maxX) {
                tempX = maxX;
            }
            if (tempY < y) {
                tempY = y;
            } else if (tempY > maxY) {
                tempY = maxY;
            }
            if (vertical) {
                value = (tempY - y) / (maxY - y);
            } else {
                value = (tempX - x) / (maxX - x);
            }
        } else
            active = isMouseOver(window);
    }

    void handleEvents(sf::RenderWindow &window, sf::Event event) {
        if (active && event.type == sf::Event::MouseButtonPressed && !mousePressed) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            mousePressed = true;
            mouseX = mousePos.x;
            mouseY = mousePos.y;
            sliderX = tempX;
            sliderY = tempY;
        }
        else if (event.type == sf::Event::MouseButtonReleased) {
            mousePressed = false;
        }
    }

    void show(bool showSlider) {
        this->showSlider = showSlider;
        active = false;
    }

    void disable(bool disableSlider) {
        this->disableSlider = disableSlider;
        active = false;
    }

    float getValue() {
        return value * 100;
    }

    void reset() {
        tempX = x;
        tempY = y;
        value = 0;
        active = false;
    }
};

Slider::Slider(int x, int y, float length, bool vertical) : ptr(new SliderImpl(x, y, length, vertical)) {
}

Slider::~Slider() {
    delete ptr;
}

void Slider::draw(sf::RenderWindow &window) {
    ptr->draw(window);
}

void Slider::update(sf::RenderWindow &window) {
    ptr->update(window);
}

void Slider::handleEvents(sf::RenderWindow &window, sf::Event event) {
    ptr->handleEvents(window, event);
}

void Slider::show(bool showSlider) {
    ptr->show(showSlider);
}

void Slider::disable(bool disableSlider) {
    ptr->disable(disableSlider);
}

float Slider::getValue() {
    return ptr->getValue();
}

void Slider::reset() {
    ptr->reset();
}

