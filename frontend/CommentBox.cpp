//
// Created by topto on 2024-05-03.
//

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include "CommentBox.h"

struct CommentBox::CommentBoxImpl {
    int x, y;
    bool showCommentBox = true;
    bool disableCommentBox = false;
    std::string text;

    bool active = false;
    bool writingComment = false;
    int writingIndex = 0;
    int writingSeperatorUpdateTime = 60;
    int writingSeperatorTime = 0;

    sf::Texture commentBoxTexture, commentBoxTextureActive;

    CommentBoxImpl(int x, int y) {
        this->x = x;
        this->y = y;
        commentBoxTexture.loadFromFile("res/commentBox.png");
        commentBoxTextureActive.loadFromFile("res/commentBoxActive.png");
        text = "Add comment...";
    }

    ~CommentBoxImpl() {

    }

    void draw(sf::RenderWindow& window) {
        if (!showCommentBox) {
            return;
        }

        // draw the comment box
        if (!writingComment){
            sf::Sprite image;
            image.setTexture(commentBoxTexture);
            image.setPosition(x, y);
            window.draw(image);
        } else {
            sf::Sprite image;
            image.setTexture(commentBoxTextureActive);
            image.setPosition(x, y);
            window.draw(image);
        }

        std::string formatedText = text;

        if (writingComment) {
            writingSeperatorTime++;
            if (writingSeperatorTime > writingSeperatorUpdateTime / 2) {
                formatedText += "|";
            }

            if (writingSeperatorTime > writingSeperatorUpdateTime) {
                writingSeperatorTime = 0;
            }
        }

        std::string text2;
        for (int i = 0; i < formatedText.size(); ++i) {
            if (i % 30 == 0 && i != 0) {
                text2 += "\n";
            }
            text2 += formatedText[i];
        }

        sf::Font font;
        font.loadFromFile("res/fonts/inter/Inter-Regular.ttf");
        sf::Text text(text2, font, 18);
        text.setPosition(x+10, y+10);
        window.draw(text);

    }

    bool isMouseOver(sf::RenderWindow& window) {
        if (showCommentBox && !disableCommentBox) {
            float Mx = sf::Mouse::getPosition(window).x;
            float My = sf::Mouse::getPosition(window).y;
            return Mx > x && Mx < x + commentBoxTexture.getSize().x && My > y && My < y + commentBoxTexture.getSize().y;
        }
        return false;
    }

    void update(sf::RenderWindow& window) {
        active = isMouseOver(window);
    }

    void handleEvents(sf::RenderWindow& window, sf::Event event) {
        if (active && event.type == sf::Event::MouseButtonPressed) {
            writingComment = true;
            if (text == "Add comment...") {
                text = "";
            }
        } else if (!active && event.type == sf::Event::MouseButtonPressed) {
            writingComment = false;
            if (text == "") {
                text = "Add comment...";
            }
        }

        if (writingComment) {
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == 8 && writingIndex > 0) {
                    text = text.substr(0, text.size()-1);
                    writingIndex--;
                } else if (event.text.unicode < 128 && event.text.unicode != 8 && writingIndex < 150) {
                    text += event.text.unicode;
                    writingIndex++;
                }
            }
        }
    }

    void setText(std::string text) {
        this->text = text;
    }

    std::string getText() {
        if (text == "Add comment...") {
            return "";
        }
        return text;
    }

    void reset() {
        active = false;
        writingComment = false;
        text = "Add comment...";
    }

    void show(bool showCommentBox) {
        this->showCommentBox = showCommentBox;
    }

    void disable(bool disableCommentBox) {
        this->disableCommentBox = disableCommentBox;
        reset();
    }
};

CommentBox::CommentBox(int x, int y) {
    ptr = new CommentBoxImpl(x, y);
}

CommentBox::~CommentBox() {
    delete ptr;
}

void CommentBox::draw(sf::RenderWindow& window) {
    ptr->draw(window);
}

void CommentBox::update(sf::RenderWindow& window) {
    ptr->update(window);
}

void CommentBox::handleEvents(sf::RenderWindow& window, sf::Event event) {
    ptr->handleEvents(window, event);
}

void CommentBox::show(bool showCommentBox) {
    ptr->show(showCommentBox);
}

void CommentBox::disable(bool disableCommentBox) {
    ptr->disable(disableCommentBox);
}

void CommentBox::setText(std::string text) {
    ptr->setText(text);
}

std::string CommentBox::getText() {
    return ptr->getText();
}

void CommentBox::reset() {
    ptr->reset();
}

// Path: frontend/CommentBox.cpp