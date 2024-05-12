//
// Created by topto on 2024-05-03.
//

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <iostream>
#include "DropBox.h"
#include "Button.h"
#include "Slider.h"
#include "CommentBox.h"

struct DisplayPoint {
    int x, y;
    std::string name;
    bool active;
};

struct DropBox::DropBoxImpl {
    int x, y;
    std::string name;
    bool showDropBox = true;
    bool disableDropBox = false;

    bool expanded = false;

    Button* expandButton;
    Button* minimizeButton;
    Slider* slider;
    CommentBox* commentBox;

    sf::Texture dropBoxTexture;
    sf::Texture dropBoxTextureExpanded;

    std::vector<std::string> items;
    std::vector<DisplayPoint> displayPoints;

    std::string selectedItem;

    sf::Texture selectHighlight;

    DropBoxImpl(int x, int y, std::string name) {
        this->x = x;
        this->y = y;
        this->name = name;

        expandButton = new Button("res/expand.png", "res/expandHighlighted.png", "res/expand.png", "res/expand.png", 320+x, 14+y+27);
        minimizeButton = new Button("res/minimize.png", "res/minimizeHighlighted.png", "res/minimize.png", "res/minimize.png", 320+x, 14+y+27);
        minimizeButton->show(false);

        dropBoxTexture.loadFromFile("res/dropBox.png");
        dropBoxTextureExpanded.loadFromFile("res/dropBoxExpanded.png");

        slider = new Slider(x+330, y+68, 147-12, true);
        slider->show(false);

        commentBox = new CommentBox(x, y+224);
        commentBox->show(false);

        selectHighlight.loadFromFile("res/selectHighlight.png");
        selectedItem = "";
    }

    ~DropBoxImpl() {

    }

    void draw(sf::RenderWindow& window) {
        if (!showDropBox) {
            return;
        }

        sf::Font font;
        font.loadFromFile("res/fonts/inter/Inter-Regular.ttf");
        sf::Text text(name, font, 22);
        text.setPosition(x + 5, y);
        window.draw(text);


        sf::Sprite image;
        image.setTexture(dropBoxTexture);
        image.setPosition(x, y+27);
        window.draw(image);

        sf::Text selectedText(selectedItem, font, 22);
        selectedText.setPosition(x + 5, y + 33);
        window.draw(selectedText);
        if (expanded) {
            sf::Sprite image2;
            image2.setTexture(dropBoxTextureExpanded);
            image2.setPosition(x, y + 68);
            window.draw(image2);
            slider->draw(window);
            commentBox->draw(window);

            for (auto & displayPoint : displayPoints) {
                if (displayPoint.active) {
                    sf::Sprite image;
                    image.setTexture(selectHighlight);
                    image.setPosition(displayPoint.x - 5, displayPoint.y);
                    window.draw(image);
                }
                sf::Text text(displayPoint.name, font, 22);
                text.setPosition(displayPoint.x, displayPoint.y);
                window.draw(text);
            }
        }
        expandButton->draw(window);
        minimizeButton->draw(window);
    }

    void update(sf::RenderWindow& window) {
        expandButton->update(window);
        minimizeButton->update(window);
        slider->update(window);
        commentBox->update(window);

        displayPoints.clear();
        if (expanded){
            int currentItem = slider->getValue()/100 * (items.size()-5);
            if (currentItem < 0)
                currentItem = 0;

            int j = 0;
            for (int i = currentItem; i < items.size(); ++i) {
                DisplayPoint displayPoint;
                displayPoint.x = x + 11;
                displayPoint.y = y + 71 + 27*j;
                displayPoint.name = items[i];
                displayPoint.active = false;
                // check if the mouse is in the display point box
                if (sf::Mouse::getPosition(window).x > displayPoint.x && sf::Mouse::getPosition(window).x < displayPoint.x + 315 &&
                    sf::Mouse::getPosition(window).y > displayPoint.y && sf::Mouse::getPosition(window).y < displayPoint.y + 24){
                    displayPoint.active = true;
                }
                displayPoints   .push_back(displayPoint);
                j++;
                if (j > 4)
                    break;
            }
        }

        if (expandButton->isPressed()){
            expanded = true;
            slider->show(true);
            commentBox->show(true);
            expandButton->show(false);
            expandButton->reset();
            minimizeButton->show(true);
        } else if (minimizeButton->isPressed()){
            expanded = false;
            slider->show(false);
            commentBox->show(false);
            minimizeButton->show(false);
            minimizeButton->reset();
            expandButton->show(true);
        }
    }

    void handleEvents(sf::RenderWindow& window, sf::Event event) {
        if (disableDropBox || !showDropBox) {
            return;
        }
        expandButton->handleEvents(window, event);
        minimizeButton->handleEvents(window, event);
        slider->handleEvents(window, event);
        commentBox->handleEvents(window, event);

        // check if the mouse is in the drop box
        if (sf::Mouse::getPosition(window).x > x && sf::Mouse::getPosition(window).x < x + 346 &&
            sf::Mouse::getPosition(window).y > y+68 && sf::Mouse::getPosition(window).y < y + 215){
            if (event.type == sf::Event::MouseButtonPressed){
                for (auto & displayPoint : displayPoints) {
                    if (displayPoint.active){
                        selectedItem = displayPoint.name;
                        break;
                    }
                }
            }
        }
    }

    void setItems(std::vector<std::string> items) {
        this->items = items;
    }

    std::string getSelectedItem() {
        return selectedItem;
    }

    void reset() {
        expandButton->reset();
        minimizeButton->reset();
        expandButton->show(true);
        minimizeButton->show(false);
        expanded = false;
        slider->reset();
        slider->show(false);
        commentBox->reset();
        commentBox->show(false);
        selectedItem = "";
    }

    void show(bool showDropBox) {
        this->showDropBox = showDropBox;
    }

    void disable(bool disableDropBox) {
        this->disableDropBox = disableDropBox;
        reset();
    }

    CommentBox* getCommentBox() {
        return commentBox;
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

CommentBox* DropBox::getCommentBox() {
    return ptr->getCommentBox();
}
