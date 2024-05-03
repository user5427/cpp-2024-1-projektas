//
// Created by topto on 2024-05-02.
//

#include <iostream>
#include <filesystem>
#include "MyWindow.h"
#include "Button.h"
#include "DropBox.h"

struct MyWindow::WindowImpl {
    sf::RenderWindow *renderWindow;
    sf::Texture windowTexture;

    Button* startButton;
    Button* pauseButton;

    DropBox* dropBox;

    WindowImpl() {
        renderWindow = new sf::RenderWindow(sf::VideoMode(863, 502), "SFML Demo");
        if (!windowTexture.loadFromFile("res/initialPage.png")) {
            std::cout << "Could not load page windowTexture" << std::endl;
            throw std::runtime_error("Could not load page windowTexture");
        }


        startButton = new Button("res/startInactive.png", "res/startHighlight.png", "res/start.png", 585, 425);
        pauseButton = new Button("res/pauseInactive.png", "res/pauseHighlight.png", "res/pause.png", 643, 425);
        dropBox = new DropBox(33, 115, "DropBox");
    }

    ~WindowImpl() {
        delete renderWindow;
    }

    void draw() {
        renderWindow->clear();
        sf::Sprite image;
        image.setTexture(windowTexture);
        image.setPosition(0, 0);
        renderWindow->draw(image);
        dropBox->draw(*renderWindow);
        startButton->draw(*renderWindow);
        pauseButton->draw(*renderWindow);

        renderWindow->display();
    }

    void update() {
        sf::Event event;

        dropBox->update(*renderWindow);
        startButton->update(*renderWindow);
        pauseButton->update(*renderWindow);
        while(renderWindow->pollEvent(event)){
            handleEvents(event);
        }


    }

    void handleEvents(sf::Event event) {
        if (event.type == sf::Event::EventType::Closed){
            renderWindow->close();
        } else {
            dropBox->handleEvents(*renderWindow, event);
            startButton->handleEvents(*renderWindow, event);
            pauseButton->handleEvents(*renderWindow, event);
        }
    }

    sf::RenderWindow* getRenderWindow() {
        return renderWindow;
    }


};

MyWindow::MyWindow() : ptr(new WindowImpl) {
}

MyWindow::~MyWindow() {
    delete ptr;
}

void MyWindow::draw() {
    ptr->draw();
}

void MyWindow::update() {
    ptr->update();
}

sf::RenderWindow* MyWindow::getRenderWindow() {
    return ptr->getRenderWindow();
}

