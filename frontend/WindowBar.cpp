//
// Created by topto on 2024-05-05.
//

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Event.hpp>
#include "WindowBar.h"
#include "Button.h"

struct WindowBar::BarImpl {
    int x, y;

    bool showWindow = true;
    bool disableWindow = false;

    bool isDragged = false;
    float prevMouseX = 0;
    float prevMouseY = 0;
    float newWindowX = 0;
    float newWindowY = 0;
    float prevWindowX = 0;
    float prevWindowY = 0;

    sf::Texture windowBarTexture;
    Button *closeButton;
    Button *collapseButton;

    BarImpl(int x, int y, sf::RenderWindow &window, int buttonStart, std::string windowBar) {
        this->x = x;
        this->y = y;
        windowBarTexture.loadFromFile(windowBar);
        closeButton = new Button("res/close.png", "res/closeHighlight.png", "res/close.png", "res/close.png",
                                 buttonStart + 50 + x, 6 + y);

        collapseButton = new Button("res/colapse.png", "res/colapseHighlight.png", "res/colapse.png", "res/colapse.png",
                                    buttonStart + x, 7 + y);
        newWindowX = window.getPosition().x;
        newWindowY = window.getPosition().y;
    }

    ~BarImpl() {
        delete closeButton;
        delete collapseButton;
    }

    void draw(sf::RenderWindow &window) {
        if (!showWindow)
            return;

        sf::Sprite windowBarSprite(windowBarTexture);
        windowBarSprite.setPosition(x, y);
        window.draw(windowBarSprite);
        closeButton->draw(window);
        collapseButton->draw(window);
    }

    void update(sf::RenderWindow &window) {
        if (disableWindow)
            return;
        closeButton->update(window);
        collapseButton->update(window);
    }

    void handleEvents(sf::RenderWindow &window, sf::Event event) {
        if (disableWindow)
            return;
        closeButton->handleEvents(window, event);
        collapseButton->handleEvents(window, event);

        if (!closeButton->isHighlighted() && !collapseButton->isHighlighted()) {
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (event.mouseButton.x >= x && event.mouseButton.x <= x + 864 &&
                        event.mouseButton.y >= y && event.mouseButton.y <= y + 28) {
                        isDragged = true;
                        prevMouseX = sf::Mouse::getPosition().x;
                        prevMouseY = sf::Mouse::getPosition().y;
                        prevWindowX = window.getPosition().x;
                        prevWindowY = window.getPosition().y;
                    }
                }
            } else if (event.type == sf::Event::MouseButtonReleased) {
                isDragged = false;
            } else if (event.type == sf::Event::MouseMoved) {
                if (isDragged) {
                    newWindowX = prevWindowX + sf::Mouse::getPosition().x - prevMouseX;
                    newWindowY = prevWindowY + sf::Mouse::getPosition().y - prevMouseY;
                }
            }
        } else
            isDragged = false;
    }

    int getWinX() {
        return newWindowX;
    }

    int getWinY() {
        return newWindowY;
    }

    void show(bool show) {
        closeButton->show(show);
        collapseButton->show(show);
        showWindow = show;
    }

    void disable(bool disable) {
        closeButton->disable(disable);
        collapseButton->disable(disable);
        disableWindow = disable;
    }

    void reset() {
        closeButton->reset();
        collapseButton->reset();
        showWindow = true;
        disableWindow = false;
    }

    bool isClosePressed() {
        return closeButton->isPressed();
    }

    bool isCollapsePressed() {
        return collapseButton->isPressed();
    }


};

WindowBar::WindowBar(int x, int y, sf::RenderWindow &window, int buttonStart, std::string windowBar) {
    pimpl = new BarImpl(x, y, window, buttonStart, windowBar);
}

WindowBar::~WindowBar() {
    delete pimpl;
}

void WindowBar::draw(sf::RenderWindow &window) {
    pimpl->draw(window);
}

void WindowBar::update(sf::RenderWindow &window) {
    pimpl->update(window);
}

void WindowBar::handleEvents(sf::RenderWindow &window, sf::Event event) {
    pimpl->handleEvents(window, event);
}

void WindowBar::show(bool show) {
    pimpl->show(show);
}

void WindowBar::disable(bool disable) {
    pimpl->disable(disable);
}

void WindowBar::reset() {
    pimpl->reset();
}

bool WindowBar::isClosePressed() {
    return pimpl->isClosePressed();
}

bool WindowBar::isCollapsePressed() {
    return pimpl->isCollapsePressed();
}

bool WindowBar::isDragged() {
    return pimpl->isDragged;
}

int WindowBar::getWinX() {
    return pimpl->getWinX();
}

int WindowBar::getWinY() {
    return pimpl->getWinY();
}

