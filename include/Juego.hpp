#pragma once
#include "menu.hpp"
#include <SFML/Graphics.hpp>

class Juego
{
private:
Menu menu;
    sf::RenderWindow window;

public:
    void run()
    {
        while (window.isOpen())
        {
            menu.printMenu(&window);
        }
    }

    Juego() : window(sf::VideoMode(1280, 720), "Spadotas")
    {
        window.setFramerateLimit(60);
    }
    ~Juego(){};
};