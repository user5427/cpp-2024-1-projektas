//
// Created by topto on 2024-05-03.
//

#ifndef CPP_2024_1_PROJEKTAS_ABSTRACTUIELEMENT_H
#define CPP_2024_1_PROJEKTAS_ABSTRACTUIELEMENT_H
class AbstractUIElement {
public:
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void update(sf::RenderWindow& window) = 0;
    virtual void handleEvents(sf::RenderWindow& window, sf::Event event) = 0;
    virtual void show(bool show) = 0;
    virtual void disable(bool disable) = 0;
    virtual void reset() = 0;

};
#endif //CPP_2024_1_PROJEKTAS_ABSTRACTUIELEMENT_H
