#pragma once
#include <SFML/Graphics.hpp>
#include "Arena.hpp"
#include "Button.hpp"
#include <iostream>
#include "Sound.hpp"

class Menu
{
public:
    void SetStartFunction(sf::RenderWindow *window)
    {

        Sound arenaMusic;
        arenaMusic.PlayMusic("assets/sounds/arenaMusic.wav");

        Arena arena(window);
        arena.Run();
    }
    void SetExitFunction()
    {

        std::cout << "Boton salida\n";
        exit(0);
    }
    void SetControlsFunction()
    {
        std::cout << "Boton controles\n";
    }
    void PrintMenu(sf::RenderWindow *menuWindow)
    {

        // Sonidos
        Sound menuMusic;
        menuMusic.PlayMusic("assets/sounds/menuMusic.wav");

        Sound titleSound;
        Sound startSound;
        Sound controlsSound;
        // Volumen
        menuMusic.SetMusicVolume(30);

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
        Button title(sf::Vector2f(1280, 288), sf::Vector2f(0, 0), &titleTexture);

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
            title.Draw(*menuWindow);
            playButton.Draw(*menuWindow);
            optionsButton.Draw(*menuWindow);
            exitButton.Draw(*menuWindow);

            // Check for button clicks
            if (playButton.GetIsPressed(*menuWindow))
            {
                menuMusic.StopMusic();
                startSound.PlaySound("assets/sounds/startSound.wav");
                SetStartFunction(menuWindow);
            }
            if (optionsButton.GetIsPressed(*menuWindow))
            {
                controlsSound.PlaySound("assets/sounds/controlsSound.wav");
                SetControlsFunction();
                inWindow = true; // Set the flag to true when controls button is pressed
            }
            if (exitButton.GetIsPressed(*menuWindow))
            {
                menuWindow->close();
                SetExitFunction();
            }
            if (title.GetIsPressed(*menuWindow))
            {

                titleSound.PlaySound("assets/sounds/titleSound.wav");
            }

            // Controls window
            if (inWindow)
            {
                sf::RectangleShape controls(sf::Vector2f(1280, 720));

                controls.setTexture(&controlsTexture);

                menuWindow->draw(controls);
                Button backButton(sf::Vector2f(250, 70), sf::Vector2f(500, 140), &backButtonTexture);
                backButton.Draw(*menuWindow);

                if (backButton.GetIsPressed(*menuWindow))
                {
                    controlsSound.PlaySound("assets/sounds/controlsSound.wav");
                    inWindow = false; // Set the flag to false when back button is pressed
                }
            }

            menuWindow->display();
        }
    }
};