//
// Created by topto on 2024-05-02.
//

#ifndef CPP_2024_1_PROJEKTAS_MYWINDOW_H
#define CPP_2024_1_PROJEKTAS_MYWINDOW_H
#include "SFML/Graphics.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "../backend/TimeTracker.h"
#include "SimulatedTimeTracker.h"

class MyWindow {
public:

    MyWindow(SimulatedTimeTracker *pTracker);
    ~MyWindow();
    void draw();
    void update();
    sf::RenderWindow* getRenderWindow();

private:
    class WindowImpl;
    WindowImpl* ptr;
};


#endif //CPP_2024_1_PROJEKTAS_MYWINDOW_H
