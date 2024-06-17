#pragma once
#include "menu.hpp"
#include <SFML/Graphics.hpp>

class Juego
{
private:
    sf::RenderWindow window;

    void Menu()
    {
        printMenu(&window);
    }

public:
    void run()
    {
        while (window.isOpen())
        {
            Menu();
        }
    }

    Juego() : window(sf::VideoMode(1280, 720), "Spadotas")
    {
        window.setFramerateLimit(60);
    }
    ~Juego(){};
};