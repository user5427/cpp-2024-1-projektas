//
// Created by topto on 2024-05-02.
//

#ifndef CPP_2024_1_PROJEKTAS_BUTTON_H
#define CPP_2024_1_PROJEKTAS_BUTTON_H


#include <SFML/Graphics/RenderWindow.hpp>

class Button {
public:
    Button(std::string inactive, std::string highlight, std::string active, int x, int y);
    ~Button();
    void draw(sf::RenderWindow& window);
    void update(sf::RenderWindow& window);
    void handleEvents(sf::RenderWindow& window, sf::Event event);
    bool isPressed();
    void reset();
    void show(bool showButton);
    void disable(bool disableButton);

private:
    class ButtonImpl;
    ButtonImpl* ptr;
};


#endif //CPP_2024_1_PROJEKTAS_BUTTON_H
