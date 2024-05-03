//
// Created by topto on 2024-05-03.
//

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include "DropBox.h"
#include "Button.h"
#include "Slider.h"

struct DropBox::DropBoxImpl {
    int x, y;
    std::string name;
    bool showDropBox = true;
    bool disableDropBox = false;

    bool expanded = false;

    Button* expandButton;
    Button* minimizeButton;
    Slider* slider;

    sf::Texture dropBoxTexture;
    sf::Texture dropBoxTextureExpanded;

    DropBoxImpl(int x, int y, std::string name) {
        this->x = x;
        this->y = y;
        this->name = name;

        expandButton = new Button("res/expand.png", "res/expandHighlighted.png", "res/expand.png", 320+x, 14+y+27);
        minimizeButton = new Button("res/minimize.png", "res/minimizeHighlighted.png", "res/minimize.png", 320+x, 14+y+27);
        minimizeButton->show(false);

        dropBoxTexture.loadFromFile("res/dropBox.png");
        dropBoxTextureExpanded.loadFromFile("res/dropBoxExpanded.png");

        slider = new Slider(x+330, y+68, 147-12, true);
        slider->show(false);
    }

    ~DropBoxImpl() {

    }

    void draw(sf::RenderWindow& window) {
        if (!showDropBox) {
            return;
        }

        sf::Sprite image;
        image.setTexture(dropBoxTexture);
        image.setPosition(x, y+27);
        window.draw(image);
        if (expanded) {
            sf::Sprite image2;
            image2.setTexture(dropBoxTextureExpanded);
            image2.setPosition(x, y + 68);
            window.draw(image2);
            slider->draw(window);
        }
        expandButton->draw(window);
        minimizeButton->draw(window);


        sf::Font font;
        font.loadFromFile("res/fonts/inter/Inter-Regular.ttf");
        sf::Text text(name, font, 22);
        text.setPosition(x + 5, y);
        window.draw(text);
    }

    void update(sf::RenderWindow& window) {
        expandButton->update(window);
        minimizeButton->update(window);
        slider->update(window);

        if (expandButton->isPressed()){
            expanded = true;
            slider->show(true);
            expandButton->show(false);
            expandButton->reset();
            minimizeButton->show(true);
        } else if (minimizeButton->isPressed()){
            expanded = false;
            slider->show(false);
            minimizeButton->show(false);
            minimizeButton->reset();
            expandButton->show(true);
        }
    }

    void handleEvents(sf::RenderWindow& window, sf::Event event) {
        if (disableDropBox) {
            return;
        }
        expandButton->handleEvents(window, event);
        minimizeButton->handleEvents(window, event);
        slider->handleEvents(window, event);
    }

    void setItems(std::vector<std::string> items) {

    }

    std::string getSelectedItem() {
        return "";
    }

    void reset() {
        expandButton->reset();
        minimizeButton->reset();
        expandButton->show(true);
        minimizeButton->show(false);
        expanded = false;
        slider->reset();
        slider->show(false);
    }

    void show(bool showDropBox) {
        this->showDropBox = showDropBox;
    }

    void disable(bool disableDropBox) {
        this->disableDropBox = disableDropBox;
        reset();
    }

};

DropBox::DropBox(int x, int y, std::string name) : ptr(new DropBoxImpl(x, y, name)) {
}

DropBox::~DropBox() {
    delete ptr;
}

void DropBox::draw(sf::RenderWindow& window) {
    ptr->draw(window);
}

void DropBox::update(sf::RenderWindow& window) {
    ptr->update(window);
}

void DropBox::handleEvents(sf::RenderWindow& window, sf::Event event) {
    ptr->handleEvents(window, event);
}

void DropBox::show(bool showDropBox) {
    ptr->show(showDropBox);
}

void DropBox::disable(bool disableDropBox) {
    ptr->disable(disableDropBox);
}

void DropBox::setItems(std::vector<std::string> items) {
    ptr->setItems(items);
}

std::string DropBox::getSelectedItem() {
    return ptr->getSelectedItem();
}

void DropBox::reset() {
    ptr->reset();
}

