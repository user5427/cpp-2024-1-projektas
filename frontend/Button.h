//
// Created by topto on 2024-05-02.
//

#ifndef CPP_2024_1_PROJEKTAS_BUTTON_H
#define CPP_2024_1_PROJEKTAS_BUTTON_H


#include <SFML/Graphics/RenderWindow.hpp>
#include "AbstractUIElement.h"

class Button : public AbstractUIElement{
public:
    Button(std::string inactive, std::string highlight, std::string active, std::string pressed, int x, int y);
    ~Button();
    void draw(sf::RenderWindow& window) override;
    void update(sf::RenderWindow& window) override;
    void handleEvents(sf::RenderWindow& window, sf::Event event) override;
    bool isPressed();
    void reset() override;
    void show(bool showButton) override;
    void disable(bool disableButton) override;

private:
    class ButtonImpl;
    ButtonImpl* ptr;
};


#endif //CPP_2024_1_PROJEKTAS_BUTTON_H
