#pragma once
#include "Menu.hpp"
#include <SFML/Graphics.hpp>

class Game
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

    Game() : window(sf::VideoMode(1280, 720), "Spadotas")
    {
        window.setFramerateLimit(60);
    }
    ~Game(){};
};