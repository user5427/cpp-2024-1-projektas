//
// Created by topto on 2024-05-03.
//

#ifndef CPP_2024_1_PROJEKTAS_COMMENTBOX_H
#define CPP_2024_1_PROJEKTAS_COMMENTBOX_H


#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include "AbstractUIElement.h"

class CommentBox : public AbstractUIElement {
public:
    CommentBox(int x, int y);
    ~CommentBox();
    void draw(sf::RenderWindow& window) override;
    void update(sf::RenderWindow& window) override;
    void handleEvents(sf::RenderWindow& window, sf::Event event) override;
    void show(bool showCommentBox) override;
    void disable(bool disableCommentBox) override;
    void setText(std::string text);
    std::string getText();
    void reset() override;
private:
    struct CommentBoxImpl;
    CommentBoxImpl* ptr;
};


#endif //CPP_2024_1_PROJEKTAS_COMMENTBOX_H
