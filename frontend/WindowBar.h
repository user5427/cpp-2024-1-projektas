//
// Created by topto on 2024-05-05.
//

#ifndef CPP_2024_1_PROJEKTAS_WINDOWBAR_H
#define CPP_2024_1_PROJEKTAS_WINDOWBAR_H


#include <SFML/Graphics/RenderWindow.hpp>
#include "AbstractUIElement.h"

class WindowBar : AbstractUIElement {
public:
    WindowBar(int x, int y, sf::RenderWindow& window);
    ~WindowBar();
    void draw(sf::RenderWindow& window) override;
    void update(sf::RenderWindow& window) override;
    void handleEvents(sf::RenderWindow& window, sf::Event event) override;
    void show(bool show) override;
    void disable(bool disable) override;
    void reset() override;

    bool isClosePressed();
    bool isCollapsePressed();
    bool isDragged();
    int getWinX();
    int getWinY();


private:
    struct BarImpl;
    BarImpl *pimpl;
};


#endif //CPP_2024_1_PROJEKTAS_WINDOWBAR_H
