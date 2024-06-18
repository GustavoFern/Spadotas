#pragma once
#include <SFML/Graphics.hpp>
#include "Arena.hpp"
#include "button.hpp"
#include <iostream>
#include "sound.hpp"

class Menu
{
public:
    void startFunction(sf::RenderWindow *window)
    {

        Sound arenaMusic;
        arenaMusic.PlayMusic("assets/sounds/arenaMusic.wav");

        Arena arena(window);
        arena.run();
    }
    void exitFunction()
    {

        std::cout << "Boton salida\n";
        exit(0);
    }
    void controlsFunction()
    {
        std::cout << "Boton controles\n";
    }
    void printMenu(sf::RenderWindow *menuWindow)
    {

        // Sonidos
        Sound menuMusic;

        menuMusic.PlayMusic("assets/sounds/menuMusic.wav");
        Sound startSound;
        Sound controlsSound;
        // Volumen
        menuMusic.musicVolume(30);

        // Texturas
        sf::Texture titleTexture;
        titleTexture.loadFromFile("assets/images/titulo.png");
        sf::Texture menuBackground;
        menuBackground.loadFromFile("assets/images/fondoMenu.png");
        sf::Texture playButtonTexture;
        playButtonTexture.loadFromFile("assets/images/playButton.png");
        sf::Texture optionsButtonTexture;
        optionsButtonTexture.loadFromFile("assets/images/controlsButton.png");
        sf::Texture exitTexture;
        exitTexture.loadFromFile("assets/images/exitButton.png");
        sf::Texture controlsTexture;
        controlsTexture.loadFromFile("assets/images/controls.png");
        sf::Texture backButtonTexture;
        backButtonTexture.loadFromFile("assets/images/back.png");

        // Creacion de botones
        Button playButton(sf::Vector2f(280, 80), sf::Vector2f(500, 350), &playButtonTexture);
        Button optionsButton(sf::Vector2f(280, 60), sf::Vector2f(500, 435), &optionsButtonTexture);
        Button exitButton(sf::Vector2f(280, 60), sf::Vector2f(500, 500), &exitTexture);
        Button backButton(sf::Vector2f(700, 130), sf::Vector2f(500, 100), &exitTexture);

        bool inWindow = false; // Add a flag to control the controls window

        sf::Event event;
        while (menuWindow->isOpen())
        {
            while (menuWindow->pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    menuWindow->close();
            }
        
            menuWindow->clear();
        
            // Dibujar fondo
            sf::RectangleShape background(sf::Vector2f(1280, 720));
            background.setTexture(&menuBackground);
            menuWindow->draw(background);
        
            // Dibujar botones
            playButton.Draw(*menuWindow);
            optionsButton.Draw(*menuWindow);
            exitButton.Draw(*menuWindow);
        
            // Check for button clicks
            if (playButton.IsPressed(*menuWindow))
            {
                menuMusic.StopMusic();
                startSound.PlaySound("assets/sounds/startSound.wav");
                startFunction(menuWindow);
            }
            if (optionsButton.IsPressed(*menuWindow))
            {
                controlsSound.PlaySound("assets/sounds/controlsSound.wav");
                controlsFunction();
                inWindow = true; // Set the flag to true when controls button is pressed
            }
            if (exitButton.IsPressed(*menuWindow))
            {
                menuWindow->close();
                exitFunction();
            }
        
            // Controls window
            if (inWindow)
            {
                sf::RectangleShape controls(sf::Vector2f(1280, 720));
        
                controls.setTexture(&controlsTexture);
        
                menuWindow->draw(controls);
                Button backButton(sf::Vector2f(250, 70), sf::Vector2f(500, 140), &backButtonTexture);
                backButton.Draw(*menuWindow);
        
                if (backButton.IsPressed(*menuWindow))
                {
                    controlsSound.PlaySound("assets/sounds/controlsSound.wav");
                    inWindow = false; // Set the flag to false when back button is pressed
                }
            }
        
            menuWindow->display();
        }
    }
};