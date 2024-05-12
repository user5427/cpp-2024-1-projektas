//
// Created by topto on 2024-05-03.
//

#ifndef CPP_2024_1_PROJEKTAS_DROPBOX_H
#define CPP_2024_1_PROJEKTAS_DROPBOX_H


#include <vector>
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include "AbstractUIElement.h"
#include "CommentBox.h"

class DropBox : public AbstractUIElement {
public:
    DropBox(int x, int y, std::string name);
    ~DropBox();
    void draw(sf::RenderWindow& window) override;
    void update(sf::RenderWindow& window) override;
    void handleEvents(sf::RenderWindow& window, sf::Event event) override;
    void show(bool showDropBox) override;
    void disable(bool disableDropBox) override;
    void setItems(std::vector<std::string> items);
    std::string getSelectedItem();
    void reset() override;
    CommentBox* getCommentBox();
private:
    class DropBoxImpl;
    DropBoxImpl* ptr;
};


#endif //CPP_2024_1_PROJEKTAS_DROPBOX_H
