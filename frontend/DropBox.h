//
// Created by topto on 2024-05-03.
//

#ifndef CPP_2024_1_PROJEKTAS_DROPBOX_H
#define CPP_2024_1_PROJEKTAS_DROPBOX_H


#include <vector>
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>

class DropBox {
public:
    DropBox(int x, int y, std::string name);
    ~DropBox();
    void draw(sf::RenderWindow& window);
    void update(sf::RenderWindow& window);
    void handleEvents(sf::RenderWindow& window, sf::Event event);
    void show(bool showDropBox);
    void disable(bool disableDropBox);
    void setItems(std::vector<std::string> items);
    std::string getSelectedItem();
    void reset();
private:
    class DropBoxImpl;
    DropBoxImpl* ptr;
};


#endif //CPP_2024_1_PROJEKTAS_DROPBOX_H
